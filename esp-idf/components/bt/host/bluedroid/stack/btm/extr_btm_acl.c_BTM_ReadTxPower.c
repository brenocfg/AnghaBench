#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBT_TRANSPORT ;
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBTM_CMPL_CB ;
struct TYPE_6__ {scalar_t__ transport; int /*<<< orphan*/  hci_handle; } ;
typedef  TYPE_2__ tACL_CONN ;
struct TYPE_5__ {int /*<<< orphan*/  tx_power_timer; int /*<<< orphan*/ * p_tx_power_cmpl_cb; int /*<<< orphan*/  read_tx_pwr_addr; } ;
struct TYPE_7__ {TYPE_1__ devcb; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/ * BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  BTM_BUSY ; 
 int /*<<< orphan*/  BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_DEV_REPLY_TIMEOUT ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTM_READ_RSSI_TYPE_CUR ; 
 int /*<<< orphan*/  BTM_TRACE_API (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_UNKNOWN_ADDR ; 
 int /*<<< orphan*/  BTU_TTYPE_BTM_ACL ; 
 scalar_t__ BT_TRANSPORT_LE ; 
 TYPE_2__* btm_bda_to_acl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__ btm_cb ; 
 int /*<<< orphan*/  btsnd_hcic_ble_read_adv_chnl_tx_power () ; 
 int /*<<< orphan*/  btsnd_hcic_read_tx_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_stop_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

tBTM_STATUS BTM_ReadTxPower (BD_ADDR remote_bda, tBT_TRANSPORT transport, tBTM_CMPL_CB *p_cb)
{
    tACL_CONN   *p;
    BOOLEAN     ret;
#define BTM_READ_RSSI_TYPE_CUR  0x00
#define BTM_READ_RSSI_TYPE_MAX  0X01

    BTM_TRACE_API ("BTM_ReadTxPower: RemBdAddr: %02x%02x%02x%02x%02x%02x\n",
                   remote_bda[0], remote_bda[1], remote_bda[2],
                   remote_bda[3], remote_bda[4], remote_bda[5]);

    /* If someone already waiting on the version, do not allow another */
    if (btm_cb.devcb.p_tx_power_cmpl_cb) {
        return (BTM_BUSY);
    }

    p = btm_bda_to_acl(remote_bda, transport);
    if (p != (tACL_CONN *)NULL) {
        btu_start_timer (&btm_cb.devcb.tx_power_timer, BTU_TTYPE_BTM_ACL,
                         BTM_DEV_REPLY_TIMEOUT);

        btm_cb.devcb.p_tx_power_cmpl_cb = p_cb;

#if BLE_INCLUDED == TRUE
        if (p->transport == BT_TRANSPORT_LE) {
            memcpy(btm_cb.devcb.read_tx_pwr_addr, remote_bda, BD_ADDR_LEN);
            ret = btsnd_hcic_ble_read_adv_chnl_tx_power();
        } else
#endif
        {
            ret = btsnd_hcic_read_tx_power (p->hci_handle, BTM_READ_RSSI_TYPE_CUR);
        }
        if (!ret) {
            btm_cb.devcb.p_tx_power_cmpl_cb = NULL;
            btu_stop_timer (&btm_cb.devcb.tx_power_timer);
            return (BTM_NO_RESOURCES);
        } else {
            return (BTM_CMD_STARTED);
        }
    }

    /* If here, no BD Addr found */
    return (BTM_UNKNOWN_ADDR);
}