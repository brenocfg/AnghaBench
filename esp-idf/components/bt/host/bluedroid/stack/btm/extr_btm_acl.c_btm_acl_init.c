#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int acl_disc_reason; int /*<<< orphan*/  btm_def_link_super_tout; int /*<<< orphan*/ * p_bl_changed_cb; scalar_t__ btm_def_link_policy; int /*<<< orphan*/ * btm_scn; int /*<<< orphan*/  acl_db; } ;

/* Variables and functions */
 int BTM_MAX_SCN ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  HCI_DEFAULT_INACT_TOUT ; 
 TYPE_1__ btm_cb ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void btm_acl_init (void)
{
    BTM_TRACE_DEBUG ("btm_acl_init\n");
#if 0  /* cleared in btm_init; put back in if called from anywhere else! */
    memset (&btm_cb.acl_db, 0, sizeof (btm_cb.acl_db));
    memset (btm_cb.btm_scn, 0, BTM_MAX_SCN);          /* Initialize the SCN usage to FALSE */
    btm_cb.btm_def_link_policy     = 0;
    btm_cb.p_bl_changed_cb         = NULL;
#endif

    /* Initialize nonzero defaults */
    btm_cb.btm_def_link_super_tout = HCI_DEFAULT_INACT_TOUT;
    btm_cb.acl_disc_reason         = 0xff ;
}