#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  void tBTM_RSSI_RESULTS ;
typedef  int /*<<< orphan*/  (* tBTM_CMPL_CB ) (void*) ;
struct TYPE_3__ {int /*<<< orphan*/  (* p_rssi_cmpl_cb ) (void*) ;int /*<<< orphan*/  (* p_rln_cmpl_cb ) (void*) ;} ;
struct TYPE_4__ {TYPE_1__ devcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_DEV_RESET ; 
 TYPE_2__ btm_cb ; 
 int /*<<< orphan*/  btm_inq_db_reset () ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 int /*<<< orphan*/  stub2 (void*) ; 

__attribute__((used)) static void btm_db_reset (void)
{
    tBTM_CMPL_CB    *p_cb;
    tBTM_STATUS      status = BTM_DEV_RESET;

    btm_inq_db_reset();

    if (btm_cb.devcb.p_rln_cmpl_cb) {
        p_cb = btm_cb.devcb.p_rln_cmpl_cb;
        btm_cb.devcb.p_rln_cmpl_cb = NULL;

        if (p_cb) {
            (*p_cb)((void *) NULL);
        }
    }

    if (btm_cb.devcb.p_rssi_cmpl_cb) {
        p_cb = btm_cb.devcb.p_rssi_cmpl_cb;
        btm_cb.devcb.p_rssi_cmpl_cb = NULL;

        if (p_cb) {
            (*p_cb)((tBTM_RSSI_RESULTS *) &status);
        }
    }
}