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
typedef  scalar_t__ tBT_TRANSPORT ;
typedef  int tBT_DEVICE_TYPE ;
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBLE_ADDR_TYPE ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_ILLEGAL_ACTION ; 
 int /*<<< orphan*/  BTM_ReadDevInfo (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int BT_DEVICE_TYPE_BLE ; 
 int BT_DEVICE_TYPE_BREDR ; 
 scalar_t__ BT_TRANSPORT_BR_EDR ; 
 scalar_t__ BT_TRANSPORT_LE ; 
 int /*<<< orphan*/  btm_sec_bond_by_transport (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

tBTM_STATUS BTM_SecBondByTransport (BD_ADDR bd_addr, tBT_TRANSPORT transport,
                                    UINT8 pin_len, UINT8 *p_pin, UINT32 trusted_mask[])
{
#if (BLE_INCLUDED == TRUE)
    tBT_DEVICE_TYPE     dev_type;
    tBLE_ADDR_TYPE      addr_type;

    BTM_ReadDevInfo(bd_addr, &dev_type, &addr_type);
    /* LE device, do SMP pairing */
    if ((transport == BT_TRANSPORT_LE && (dev_type & BT_DEVICE_TYPE_BLE) == 0) ||
            (transport == BT_TRANSPORT_BR_EDR && (dev_type & BT_DEVICE_TYPE_BREDR) == 0)) {
        return BTM_ILLEGAL_ACTION;
    }
#endif  ///BLE_INCLUDED == TRUE

    return btm_sec_bond_by_transport(bd_addr, transport, pin_len, p_pin, trusted_mask);
}