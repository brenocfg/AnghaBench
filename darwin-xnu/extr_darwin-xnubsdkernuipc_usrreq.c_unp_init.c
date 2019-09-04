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
struct unpcb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int MCLBYTES ; 
 int UIPC_MAX_CMSG_FD ; 
 int /*<<< orphan*/  _CASSERT (int) ; 
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 void* lck_mtx_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lck_rw_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nmbclusters ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/ * unp_connect_lock ; 
 int /*<<< orphan*/  unp_dhead ; 
 int /*<<< orphan*/ * unp_disconnect_lock ; 
 int /*<<< orphan*/ * unp_list_mtx ; 
 int /*<<< orphan*/  unp_mtx_attr ; 
 int /*<<< orphan*/  unp_mtx_grp ; 
 int /*<<< orphan*/  unp_mtx_grp_attr ; 
 int /*<<< orphan*/  unp_shead ; 
 scalar_t__ unp_zone ; 
 scalar_t__ zinit (int,int,int,char*) ; 

void
unp_init(void)
{
	_CASSERT(UIPC_MAX_CMSG_FD >= (MCLBYTES / sizeof(int)));
	unp_zone = zinit(sizeof (struct unpcb),
	    (nmbclusters * sizeof (struct unpcb)), 4096, "unpzone");

	if (unp_zone == 0)
		panic("unp_init");
	LIST_INIT(&unp_dhead);
	LIST_INIT(&unp_shead);

	/*
	 * allocate lock group attribute and group for udp pcb mutexes
	 */
	unp_mtx_grp_attr = lck_grp_attr_alloc_init();

	unp_mtx_grp = lck_grp_alloc_init("unp_list", unp_mtx_grp_attr);

	unp_mtx_attr = lck_attr_alloc_init();

	if ((unp_list_mtx = lck_rw_alloc_init(unp_mtx_grp,
	    unp_mtx_attr)) == NULL)
		return;	/* pretty much dead if this fails... */

	if ((unp_disconnect_lock = lck_mtx_alloc_init(unp_mtx_grp,
		unp_mtx_attr)) == NULL)
		return;

	if ((unp_connect_lock = lck_mtx_alloc_init(unp_mtx_grp,
		unp_mtx_attr)) == NULL)
		return;
}