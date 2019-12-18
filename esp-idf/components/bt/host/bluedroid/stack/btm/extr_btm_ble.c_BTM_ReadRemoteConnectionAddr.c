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
struct TYPE_6__ {int /*<<< orphan*/  ble_addr_type; } ;
struct TYPE_7__ {TYPE_1__ ble; } ;
typedef  TYPE_2__ tBTM_SEC_DEV_REC ;
typedef  int /*<<< orphan*/  tBLE_ADDR_TYPE ;
struct TYPE_8__ {int /*<<< orphan*/  active_remote_addr_type; int /*<<< orphan*/  active_remote_addr; } ;
typedef  TYPE_3__ tACL_CONN ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  BT_TRANSPORT_LE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__* btm_bda_to_acl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* btm_find_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOLEAN BTM_ReadRemoteConnectionAddr(BD_ADDR pseudo_addr, BD_ADDR conn_addr,
                                     tBLE_ADDR_TYPE *p_addr_type)
{
    BOOLEAN         st = TRUE;
#if (BLE_PRIVACY_SPT == TRUE)
    tACL_CONN       *p = btm_bda_to_acl (pseudo_addr, BT_TRANSPORT_LE);

    if (p == NULL) {
        BTM_TRACE_ERROR("BTM_ReadRemoteConnectionAddr can not find connection"
                        " with matching address");
        return FALSE;
    }

    memcpy(conn_addr, p->active_remote_addr, BD_ADDR_LEN);
    *p_addr_type = p->active_remote_addr_type;
#else
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_dev(pseudo_addr);

    memcpy(conn_addr, pseudo_addr, BD_ADDR_LEN);
    if (p_dev_rec != NULL) {
        *p_addr_type = p_dev_rec->ble.ble_addr_type;
    }
#endif
    return st;

}