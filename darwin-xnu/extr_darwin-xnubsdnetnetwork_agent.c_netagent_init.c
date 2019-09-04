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
typedef  scalar_t__ errno_t ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NETAGENTLOG0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NETAGENT_CONTROL_NAME ; 
 int /*<<< orphan*/  ctl_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_attr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lck_grp_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_attr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  master_netagent_list ; 
 int /*<<< orphan*/ * netagent_grp_attr ; 
 int /*<<< orphan*/ * netagent_kctlref ; 
 int /*<<< orphan*/  netagent_lock ; 
 int /*<<< orphan*/ * netagent_mtx_attr ; 
 int /*<<< orphan*/ * netagent_mtx_grp ; 
 scalar_t__ netagent_register_control () ; 

errno_t
netagent_init(void)
{
	errno_t result = 0;

	result = netagent_register_control();
	if (result != 0) {
		goto done;
	}

	netagent_grp_attr = lck_grp_attr_alloc_init();
	if (netagent_grp_attr == NULL) {
		NETAGENTLOG0(LOG_ERR, "lck_grp_attr_alloc_init failed");
		result = ENOMEM;
		goto done;
	}

	netagent_mtx_grp = lck_grp_alloc_init(NETAGENT_CONTROL_NAME, netagent_grp_attr);
	if (netagent_mtx_grp == NULL) {
		NETAGENTLOG0(LOG_ERR, "lck_grp_alloc_init failed");
		result = ENOMEM;
		goto done;
	}

	netagent_mtx_attr = lck_attr_alloc_init();
	if (netagent_mtx_attr == NULL) {
		NETAGENTLOG0(LOG_ERR, "lck_attr_alloc_init failed");
		result = ENOMEM;
		goto done;
	}

	lck_rw_init(&netagent_lock, netagent_mtx_grp, netagent_mtx_attr);

	LIST_INIT(&master_netagent_list);

done:
	if (result != 0) {
		if (netagent_mtx_attr != NULL) {
			lck_attr_free(netagent_mtx_attr);
			netagent_mtx_attr = NULL;
		}
		if (netagent_mtx_grp != NULL) {
			lck_grp_free(netagent_mtx_grp);
			netagent_mtx_grp = NULL;
		}
		if (netagent_grp_attr != NULL) {
			lck_grp_attr_free(netagent_grp_attr);
			netagent_grp_attr = NULL;
		}
		if (netagent_kctlref != NULL) {
			ctl_deregister(netagent_kctlref);
			netagent_kctlref = NULL;
		}
	}
	return (result);
}