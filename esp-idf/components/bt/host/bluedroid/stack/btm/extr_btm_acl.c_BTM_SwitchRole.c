#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tBTM_STATUS ;
struct TYPE_14__ {int sec_flags; int /*<<< orphan*/  rs_disc_pending; } ;
typedef  TYPE_3__ tBTM_SEC_DEV_REC ;
struct TYPE_15__ {int /*<<< orphan*/  mode; } ;
typedef  TYPE_4__ tBTM_PM_PWR_MD ;
typedef  scalar_t__ tBTM_PM_MODE ;
typedef  int /*<<< orphan*/  tBTM_CMPL_CB ;
struct TYPE_16__ {scalar_t__ link_role; scalar_t__ switch_role_state; scalar_t__ encrypt_state; int /*<<< orphan*/  hci_handle; int /*<<< orphan*/  remote_addr; } ;
typedef  TYPE_5__ tACL_CONN ;
typedef  int /*<<< orphan*/  settings ;
typedef  scalar_t__ UINT8 ;
struct TYPE_12__ {int /*<<< orphan*/  hci_status; scalar_t__ role; int /*<<< orphan*/ * remote_bd_addr; } ;
struct TYPE_13__ {int /*<<< orphan*/ * p_switch_role_cb; TYPE_1__ switch_role_ref_data; } ;
struct TYPE_18__ {TYPE_2__ devcb; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* supports_master_slave_role_switch ) () ;} ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/ * BD_ADDR_PTR ;
typedef  int /*<<< orphan*/ * BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 scalar_t__ BTM_ACL_ENCRYPT_STATE_ENCRYPT_OFF ; 
 scalar_t__ BTM_ACL_SWKEY_STATE_ENCRYPTION_OFF ; 
 scalar_t__ BTM_ACL_SWKEY_STATE_IDLE ; 
 scalar_t__ BTM_ACL_SWKEY_STATE_IN_PROGRESS ; 
 scalar_t__ BTM_ACL_SWKEY_STATE_MODE_CHANGE ; 
 scalar_t__ BTM_BUSY ; 
 scalar_t__ BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_EPR_AVAILABLE (TYPE_5__*) ; 
 scalar_t__ BTM_MODE_UNSUPPORTED ; 
 scalar_t__ BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTM_PM_MD_ACTIVE ; 
 scalar_t__ BTM_PM_MD_PARK ; 
 scalar_t__ BTM_PM_MD_SNIFF ; 
 int /*<<< orphan*/  BTM_PM_SET_ONLY_ID ; 
 scalar_t__ BTM_ReadPowerMode (int /*<<< orphan*/ ,scalar_t__*) ; 
 int BTM_SEC_ENCRYPTED ; 
 int /*<<< orphan*/  BTM_SEC_RS_PENDING ; 
 scalar_t__ BTM_SUCCESS ; 
 scalar_t__ BTM_SetPowerMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  BTM_TRACE_API (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,scalar_t__,...) ; 
 scalar_t__ BTM_UNKNOWN_ADDR ; 
 scalar_t__ BTM_WRONG_MODE ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HCI_ERR_UNSUPPORTED_VALUE ; 
 scalar_t__ TRUE ; 
 TYPE_5__* btm_bda_to_acl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_8__ btm_cb ; 
 TYPE_3__* btm_find_dev (int /*<<< orphan*/ *) ; 
 scalar_t__ btm_is_sco_active_by_bdaddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btsnd_hcic_set_conn_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btsnd_hcic_switch_role (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_6__* controller_get_interface () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 () ; 

tBTM_STATUS BTM_SwitchRole (BD_ADDR remote_bd_addr, UINT8 new_role, tBTM_CMPL_CB *p_cb)
{
    tACL_CONN   *p;
    tBTM_SEC_DEV_REC  *p_dev_rec = NULL;
#if BTM_SCO_INCLUDED == TRUE
    BOOLEAN    is_sco_active;
#endif
    tBTM_STATUS  status;
    tBTM_PM_MODE pwr_mode;
    tBTM_PM_PWR_MD settings;
#if (BT_USE_TRACES == TRUE)
    BD_ADDR_PTR  p_bda;
#endif
    BTM_TRACE_API ("BTM_SwitchRole BDA: %02x-%02x-%02x-%02x-%02x-%02x\n",
                   remote_bd_addr[0], remote_bd_addr[1], remote_bd_addr[2],
                   remote_bd_addr[3], remote_bd_addr[4], remote_bd_addr[5]);

    /* Make sure the local device supports switching */
    if (!controller_get_interface()->supports_master_slave_role_switch()) {
        return (BTM_MODE_UNSUPPORTED);
    }

    if (btm_cb.devcb.p_switch_role_cb && p_cb) {
#if (BT_USE_TRACES == TRUE)
        p_bda = btm_cb.devcb.switch_role_ref_data.remote_bd_addr;
        BTM_TRACE_DEBUG ("Role switch on other device is in progress 0x%02x%02x%02x%02x%02x%02x\n",
                         p_bda[0], p_bda[1], p_bda[2],
                         p_bda[3], p_bda[4], p_bda[5]);
#endif
        return (BTM_BUSY);
    }

    if ((p = btm_bda_to_acl(remote_bd_addr, BT_TRANSPORT_BR_EDR)) == NULL) {
        return (BTM_UNKNOWN_ADDR);
    }

    /* Finished if already in desired role */
    if (p->link_role == new_role) {
        return (BTM_SUCCESS);
    }

#if BTM_SCO_INCLUDED == TRUE
    /* Check if there is any SCO Active on this BD Address */
    is_sco_active = btm_is_sco_active_by_bdaddr(remote_bd_addr);

    if (is_sco_active == TRUE) {
        return (BTM_NO_RESOURCES);
    }
#endif

    /* Ignore role switch request if the previous request was not completed */
    if (p->switch_role_state != BTM_ACL_SWKEY_STATE_IDLE) {
        BTM_TRACE_DEBUG ("BTM_SwitchRole busy: %d\n",
                         p->switch_role_state);
        return (BTM_BUSY);
    }

    if ((status = BTM_ReadPowerMode(p->remote_addr, &pwr_mode)) != BTM_SUCCESS) {
        return (status);
    }

    /* Wake up the link if in sniff or park before attempting switch */
    if (pwr_mode == BTM_PM_MD_PARK || pwr_mode == BTM_PM_MD_SNIFF) {
        memset( (void *)&settings, 0, sizeof(settings));
        settings.mode = BTM_PM_MD_ACTIVE;
        status = BTM_SetPowerMode (BTM_PM_SET_ONLY_ID, p->remote_addr, &settings);
        if (status != BTM_CMD_STARTED) {
            return (BTM_WRONG_MODE);
        }

        p->switch_role_state = BTM_ACL_SWKEY_STATE_MODE_CHANGE;
    }
    /* some devices do not support switch while encryption is on */
    else {
        p_dev_rec = btm_find_dev (remote_bd_addr);
        if ((p_dev_rec != NULL)
                && ((p_dev_rec->sec_flags & BTM_SEC_ENCRYPTED) != 0)
                && !BTM_EPR_AVAILABLE(p)) {
            /* bypass turning off encryption if change link key is already doing it */
            if (p->encrypt_state != BTM_ACL_ENCRYPT_STATE_ENCRYPT_OFF) {
                if (!btsnd_hcic_set_conn_encrypt (p->hci_handle, FALSE)) {
                    return (BTM_NO_RESOURCES);
                } else {
                    p->encrypt_state = BTM_ACL_ENCRYPT_STATE_ENCRYPT_OFF;
                }
            }

            p->switch_role_state = BTM_ACL_SWKEY_STATE_ENCRYPTION_OFF;
        } else {
            if (!btsnd_hcic_switch_role (remote_bd_addr, new_role)) {
                return (BTM_NO_RESOURCES);
            }

            p->switch_role_state = BTM_ACL_SWKEY_STATE_IN_PROGRESS;

#if BTM_DISC_DURING_RS == TRUE
            if (p_dev_rec) {
                p_dev_rec->rs_disc_pending = BTM_SEC_RS_PENDING;
            }
#endif
        }
    }

    /* Initialize return structure in case request fails */
    if (p_cb) {
        memcpy (btm_cb.devcb.switch_role_ref_data.remote_bd_addr, remote_bd_addr,
                BD_ADDR_LEN);
        btm_cb.devcb.switch_role_ref_data.role = new_role;
        /* initialized to an error code */
        btm_cb.devcb.switch_role_ref_data.hci_status = HCI_ERR_UNSUPPORTED_VALUE;
        btm_cb.devcb.p_switch_role_cb = p_cb;
    }
    return (BTM_CMD_STARTED);
}