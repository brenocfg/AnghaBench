#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBT_TRANSPORT ;
struct TYPE_4__ {int /*<<< orphan*/  pseudo_addr; } ;
struct TYPE_5__ {int device_type; TYPE_1__ ble; int /*<<< orphan*/  bd_addr; } ;
typedef  TYPE_2__ tBTM_SEC_DEV_REC ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int BT_DEVICE_TYPE_BREDR ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 int /*<<< orphan*/  BT_TRANSPORT_LE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * btm_bda_to_acl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* btm_find_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOLEAN BTM_ReadConnectedTransportAddress(BD_ADDR remote_bda, tBT_TRANSPORT transport)
{
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_dev(remote_bda);

    /* if no device can be located, return */
    if (p_dev_rec == NULL) {
        memset(remote_bda, 0, BD_ADDR_LEN);
        return FALSE;
    }

    if (transport == BT_TRANSPORT_BR_EDR) {
        if (btm_bda_to_acl(p_dev_rec->bd_addr, transport) != NULL) {
            memcpy(remote_bda, p_dev_rec->bd_addr, BD_ADDR_LEN);
            return TRUE;
        } else if (p_dev_rec->device_type & BT_DEVICE_TYPE_BREDR) {
            memcpy(remote_bda, p_dev_rec->bd_addr, BD_ADDR_LEN);
        } else {
            memset(remote_bda, 0, BD_ADDR_LEN);
        }
        return FALSE;
    }
#if (BLE_INCLUDED == TRUE)
    if (transport == BT_TRANSPORT_LE) {
        memcpy(remote_bda, p_dev_rec->ble.pseudo_addr, BD_ADDR_LEN);
        if (btm_bda_to_acl(p_dev_rec->ble.pseudo_addr, transport) != NULL) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
#endif  ///BLE_INCLUDED == TRUE
    return FALSE;
}