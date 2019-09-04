#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct necp_fd_data {int dummy; } ;
struct necp_client_flow_registration {int dummy; } ;
struct necp_client_flow {int dummy; } ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MCR_SLEEP ; 
 int NECP_CLIENT_FD_ZONE_MAX ; 
 int /*<<< orphan*/  NECP_CLIENT_FD_ZONE_NAME ; 
 int /*<<< orphan*/  NECP_FLOW_REGISTRATION_ZONE_NAME ; 
 int /*<<< orphan*/  NECP_FLOW_ZONE_NAME ; 
 int /*<<< orphan*/  RB_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THREAD_CALL_OPTIONS_ONCE ; 
 int /*<<< orphan*/  THREAD_CALL_PRIORITY_KERNEL ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lck_attr_alloc_init () ; 
 int /*<<< orphan*/ * lck_grp_alloc_init (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_rw_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* mcache_create (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int necp_client_fd_size ; 
 int /*<<< orphan*/ * necp_client_fd_zone ; 
 int /*<<< orphan*/  necp_client_flow_global_tree ; 
 int /*<<< orphan*/  necp_client_global_tree ; 
 int /*<<< orphan*/  necp_client_tree_lock ; 
 int /*<<< orphan*/ * necp_client_update_tcall ; 
 int /*<<< orphan*/  necp_collect_stats_flow_list ; 
 int /*<<< orphan*/  necp_collect_stats_list_lock ; 
 int /*<<< orphan*/ * necp_fd_grp_attr ; 
 int /*<<< orphan*/  necp_fd_list ; 
 int /*<<< orphan*/  necp_fd_lock ; 
 int /*<<< orphan*/ * necp_fd_mtx_attr ; 
 int /*<<< orphan*/ * necp_fd_mtx_grp ; 
 int /*<<< orphan*/  necp_fd_observer_list ; 
 int /*<<< orphan*/ * necp_flow_cache ; 
 int /*<<< orphan*/ * necp_flow_registration_cache ; 
 int necp_flow_registration_size ; 
 int necp_flow_size ; 
 int /*<<< orphan*/  necp_flow_tree_lock ; 
 int /*<<< orphan*/  necp_observer_lock ; 
 int /*<<< orphan*/  necp_update_all_clients_callout ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/ * thread_call_allocate_with_options (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zinit (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

errno_t
necp_client_init(void)
{
	necp_fd_grp_attr = lck_grp_attr_alloc_init();
	if (necp_fd_grp_attr == NULL) {
		panic("lck_grp_attr_alloc_init failed\n");
		/* NOTREACHED */
	}

	necp_fd_mtx_grp = lck_grp_alloc_init("necp_fd", necp_fd_grp_attr);
	if (necp_fd_mtx_grp == NULL) {
		panic("lck_grp_alloc_init failed\n");
		/* NOTREACHED */
	}

	necp_fd_mtx_attr = lck_attr_alloc_init();
	if (necp_fd_mtx_attr == NULL) {
		panic("lck_attr_alloc_init failed\n");
		/* NOTREACHED */
	}

	necp_client_fd_size = sizeof(struct necp_fd_data);
	necp_client_fd_zone = zinit(necp_client_fd_size,
								NECP_CLIENT_FD_ZONE_MAX * necp_client_fd_size,
								0, NECP_CLIENT_FD_ZONE_NAME);
	if (necp_client_fd_zone == NULL) {
		panic("zinit(necp_client_fd) failed\n");
		/* NOTREACHED */
	}

	necp_flow_size = sizeof(struct necp_client_flow);
	necp_flow_cache = mcache_create(NECP_FLOW_ZONE_NAME, necp_flow_size, sizeof (uint64_t), 0, MCR_SLEEP);
	if (necp_flow_cache == NULL) {
		panic("mcache_create(necp_flow_cache) failed\n");
		/* NOTREACHED */
	}

	necp_flow_registration_size = sizeof(struct necp_client_flow_registration);
	necp_flow_registration_cache = mcache_create(NECP_FLOW_REGISTRATION_ZONE_NAME, necp_flow_registration_size, sizeof (uint64_t), 0, MCR_SLEEP);
	if (necp_flow_registration_cache == NULL) {
		panic("mcache_create(necp_client_flow_registration) failed\n");
		/* NOTREACHED */
	}

	necp_client_update_tcall = thread_call_allocate_with_options(necp_update_all_clients_callout, NULL,
																 THREAD_CALL_PRIORITY_KERNEL, THREAD_CALL_OPTIONS_ONCE);
	VERIFY(necp_client_update_tcall != NULL);

	lck_rw_init(&necp_fd_lock, necp_fd_mtx_grp, necp_fd_mtx_attr);
	lck_rw_init(&necp_observer_lock, necp_fd_mtx_grp, necp_fd_mtx_attr);
	lck_rw_init(&necp_client_tree_lock, necp_fd_mtx_grp, necp_fd_mtx_attr);
    lck_rw_init(&necp_flow_tree_lock, necp_fd_mtx_grp, necp_fd_mtx_attr);
	lck_rw_init(&necp_collect_stats_list_lock, necp_fd_mtx_grp, necp_fd_mtx_attr);

	LIST_INIT(&necp_fd_list);
	LIST_INIT(&necp_fd_observer_list);
	LIST_INIT(&necp_collect_stats_flow_list);

	RB_INIT(&necp_client_global_tree);
	RB_INIT(&necp_client_flow_global_tree);

	return (0);
}