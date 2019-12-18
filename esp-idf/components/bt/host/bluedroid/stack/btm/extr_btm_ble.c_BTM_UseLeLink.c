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
typedef  scalar_t__ tBT_DEVICE_TYPE ;
typedef  int /*<<< orphan*/  tBLE_ADDR_TYPE ;
typedef  int /*<<< orphan*/  tACL_CONN ;
typedef  int BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_ReadDevInfo (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ BT_DEVICE_TYPE_BLE ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 int /*<<< orphan*/  BT_TRANSPORT_LE ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/ * btm_bda_to_acl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOLEAN BTM_UseLeLink (BD_ADDR bd_addr)
{
    tACL_CONN         *p;
    tBT_DEVICE_TYPE     dev_type;
    tBLE_ADDR_TYPE      addr_type;
    BOOLEAN             use_le = FALSE;

    if ((p = btm_bda_to_acl(bd_addr, BT_TRANSPORT_BR_EDR)) != NULL) {
        return use_le;
    } else if ((p = btm_bda_to_acl(bd_addr, BT_TRANSPORT_LE)) != NULL) {
        use_le = TRUE;
    } else {
        BTM_ReadDevInfo(bd_addr, &dev_type, &addr_type);
        use_le = (dev_type == BT_DEVICE_TYPE_BLE);
    }
    return use_le;
}