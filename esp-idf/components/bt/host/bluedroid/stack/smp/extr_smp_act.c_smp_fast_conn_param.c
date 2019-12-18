#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSMP_INT_DATA ;
struct TYPE_7__ {scalar_t__ role; int /*<<< orphan*/  pairing_bda; } ;
typedef  TYPE_2__ tSMP_CB ;
struct TYPE_6__ {scalar_t__ skip_update_conn_param; } ;
struct TYPE_8__ {TYPE_1__ ble; } ;
typedef  TYPE_3__ tBTM_SEC_DEV_REC ;

/* Variables and functions */
 scalar_t__ BTM_ROLE_MASTER ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  L2CA_EnableUpdateBleConnParams (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* btm_find_dev (int /*<<< orphan*/ ) ; 

void smp_fast_conn_param(tSMP_CB *p_cb, tSMP_INT_DATA *p_data)
{
    if(p_cb->role == BTM_ROLE_MASTER) {
        L2CA_EnableUpdateBleConnParams(p_cb->pairing_bda, FALSE);
    }
#if (SMP_SLAVE_CON_PARAMS_UPD_ENABLE == TRUE)
    else {
        tBTM_SEC_DEV_REC    *p_rec = btm_find_dev (p_cb->pairing_bda);
        if(p_rec && p_rec->ble.skip_update_conn_param) {
            //do nothing
            return;
        }
        /* Disable L2CAP connection parameter updates while bonding since
        some peripherals are not able to revert to fast connection parameters
        during the start of service discovery. Connection paramter updates
        get enabled again once service discovery completes. */
        L2CA_EnableUpdateBleConnParams(p_cb->pairing_bda, FALSE);
    }
#endif
}