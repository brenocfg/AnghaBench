#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int packet_types; } ;
struct TYPE_12__ {int /*<<< orphan*/  bd_addr; } ;
struct TYPE_13__ {TYPE_6__ setup; TYPE_1__ data; } ;
struct TYPE_15__ {scalar_t__ state; scalar_t__ is_orig; int /*<<< orphan*/  hci_handle; int /*<<< orphan*/ * p_disc_cb; int /*<<< orphan*/ * p_conn_cb; TYPE_2__ esco; scalar_t__ rem_bd_known; } ;
typedef  TYPE_4__ tSCO_CONN ;
typedef  scalar_t__ tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBTM_SCO_CB ;
struct TYPE_16__ {int /*<<< orphan*/  mode; } ;
typedef  TYPE_5__ tBTM_PM_PWR_MD ;
typedef  scalar_t__ tBTM_PM_MODE ;
typedef  TYPE_6__ tBTM_ESCO_PARAMS ;
struct TYPE_18__ {scalar_t__ switch_role_state; } ;
typedef  TYPE_7__ tACL_CONN ;
typedef  int /*<<< orphan*/  pm ;
typedef  scalar_t__ UINT8 ;
typedef  int UINT16 ;
struct TYPE_14__ {scalar_t__ desired_sco_mode; TYPE_6__ def_esco_parms; TYPE_4__* sco_db; } ;
struct TYPE_19__ {int btm_sco_pkt_types_supported; TYPE_3__ sco_cb; } ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 scalar_t__ BTM_ACL_SWKEY_STATE_IDLE ; 
 scalar_t__ BTM_BUSY ; 
 scalar_t__ BTM_CMD_STARTED ; 
 int BTM_GetHCIConnHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BTM_IGNORE_SCO_PKT_TYPE ; 
 int /*<<< orphan*/  BTM_INVALID_HCI_HANDLE ; 
 int BTM_INVALID_SCO_INDEX ; 
 scalar_t__ BTM_LINK_TYPE_SCO ; 
 int BTM_MAX_SCO_LINKS ; 
 scalar_t__ BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTM_PM_MD_ACTIVE ; 
 scalar_t__ BTM_PM_MD_PARK ; 
 scalar_t__ BTM_PM_MD_SNIFF ; 
 int /*<<< orphan*/  BTM_PM_SET_ONLY_ID ; 
 scalar_t__ BTM_ReadPowerMode (int /*<<< orphan*/ ,scalar_t__*) ; 
 int BTM_SCO_EXCEPTION_PKTS_MASK ; 
 int BTM_SCO_LINK_ONLY_MASK ; 
 int BTM_SCO_SUPPORTED_PKTS_MASK ; 
 scalar_t__ BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_SetPowerMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  BTM_TRACE_API (char*,int,...) ; 
 scalar_t__ BTM_UNKNOWN_ADDR ; 
 scalar_t__ BTM_WRONG_MODE ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 scalar_t__ FALSE ; 
 scalar_t__ HCI_LINK_TYPE_ESCO ; 
 scalar_t__ SCO_ST_CONNECTING ; 
 scalar_t__ SCO_ST_LISTENING ; 
 scalar_t__ SCO_ST_PEND_ROLECHANGE ; 
 scalar_t__ SCO_ST_PEND_UNPARK ; 
 scalar_t__ SCO_ST_UNUSED ; 
 scalar_t__ TRUE ; 
 TYPE_7__* btm_bda_to_acl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_9__ btm_cb ; 
 scalar_t__ btm_send_connect_request (int,TYPE_6__*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

tBTM_STATUS BTM_CreateSco (BD_ADDR remote_bda, BOOLEAN is_orig, UINT16 pkt_types,
                           UINT16 *p_sco_inx, tBTM_SCO_CB *p_conn_cb,
                           tBTM_SCO_CB *p_disc_cb)
{
#if (BTM_MAX_SCO_LINKS > 0)
    tBTM_ESCO_PARAMS *p_setup;
    tSCO_CONN        *p = &btm_cb.sco_cb.sco_db[0];
    UINT16            xx;
    UINT16            acl_handle = 0;
    UINT16            temp_pkt_types;
    tACL_CONN        *p_acl;

#if (BTM_SCO_WAKE_PARKED_LINK == TRUE)
    tBTM_PM_MODE      md;
    tBTM_PM_PWR_MD    pm;
#else  // BTM_SCO_WAKE_PARKED_LINK
    UINT8             mode;
#endif  // BTM_SCO_WAKE_PARKED_LINK

    *p_sco_inx = BTM_INVALID_SCO_INDEX;

    /* If originating, ensure that there is an ACL connection to the BD Address */
    if (is_orig) {
        if ((!remote_bda) || ((acl_handle = BTM_GetHCIConnHandle (remote_bda, BT_TRANSPORT_BR_EDR)) == 0xFFFF)) {
            return (BTM_UNKNOWN_ADDR);
        }
    }

    if (remote_bda) {
        /* If any SCO is being established to the remote BD address, refuse this */
        for (xx = 0; xx < BTM_MAX_SCO_LINKS; xx++, p++) {
            if (((p->state == SCO_ST_CONNECTING) || (p->state == SCO_ST_LISTENING)
                    || (p->state == SCO_ST_PEND_UNPARK))
                    && (!memcmp (p->esco.data.bd_addr, remote_bda, BD_ADDR_LEN))) {
                return (BTM_BUSY);
            }
        }
    } else {
        /* Support only 1 wildcard BD address at a time */
        for (xx = 0; xx < BTM_MAX_SCO_LINKS; xx++, p++) {
            if ((p->state == SCO_ST_LISTENING) && (!p->rem_bd_known)) {
                return (BTM_BUSY);
            }
        }
    }

    /* Now, try to find an unused control block, and kick off the SCO establishment */
    for (xx = 0, p = &btm_cb.sco_cb.sco_db[0]; xx < BTM_MAX_SCO_LINKS; xx++, p++) {
        if (p->state == SCO_ST_UNUSED) {
            if (remote_bda) {
                if (is_orig) {
                    /* can not create SCO link if in park mode */
#if BTM_SCO_WAKE_PARKED_LINK == TRUE
                    if (BTM_ReadPowerMode(remote_bda, &md) == BTM_SUCCESS) {
                        if (md == BTM_PM_MD_PARK || md == BTM_PM_MD_SNIFF) {
                            memset( (void *)&pm, 0, sizeof(pm));
                            pm.mode = BTM_PM_MD_ACTIVE;
                            BTM_SetPowerMode(BTM_PM_SET_ONLY_ID, remote_bda, &pm);
                            p->state = SCO_ST_PEND_UNPARK;
                        }
                    }
#else  // BTM_SCO_WAKE_PARKED_LINK
                    if ( (BTM_ReadPowerMode(remote_bda, &mode) == BTM_SUCCESS) && (mode == BTM_PM_MD_PARK) ) {
                        return (BTM_WRONG_MODE);
                    }
#endif  // BTM_SCO_WAKE_PARKED_LINK
                }
                memcpy (p->esco.data.bd_addr, remote_bda, BD_ADDR_LEN);
                p->rem_bd_known = TRUE;
            } else {
                p->rem_bd_known = FALSE;
            }

            /* Link role is ignored in for this message */
            if (pkt_types == BTM_IGNORE_SCO_PKT_TYPE) {
                pkt_types = btm_cb.sco_cb.def_esco_parms.packet_types;
            }

            p_setup = &p->esco.setup;
            *p_setup = btm_cb.sco_cb.def_esco_parms;
            p_setup->packet_types = (btm_cb.sco_cb.desired_sco_mode == BTM_LINK_TYPE_SCO)
                                    ? (pkt_types & BTM_SCO_LINK_ONLY_MASK) : pkt_types;

            temp_pkt_types = (p_setup->packet_types & BTM_SCO_SUPPORTED_PKTS_MASK &
                              btm_cb.btm_sco_pkt_types_supported);

            /* OR in any exception packet types */
            if (btm_cb.sco_cb.desired_sco_mode == HCI_LINK_TYPE_ESCO) {
                temp_pkt_types |= ((p_setup->packet_types & BTM_SCO_EXCEPTION_PKTS_MASK) |
                                   (btm_cb.btm_sco_pkt_types_supported & BTM_SCO_EXCEPTION_PKTS_MASK));
            } else { /* Only using SCO packet types; turn off EDR also */
                temp_pkt_types |= BTM_SCO_EXCEPTION_PKTS_MASK;
            }

            p_setup->packet_types = temp_pkt_types;
            p->p_conn_cb  = p_conn_cb;
            p->p_disc_cb  = p_disc_cb;
            p->hci_handle = BTM_INVALID_HCI_HANDLE;
            p->is_orig = is_orig;

            if ( p->state != SCO_ST_PEND_UNPARK ) {
                if (is_orig) {
                    /* If role change is in progress, do not proceed with SCO setup
                     * Wait till role change is complete */
                    p_acl = btm_bda_to_acl(remote_bda, BT_TRANSPORT_BR_EDR);
                    if (p_acl && p_acl->switch_role_state != BTM_ACL_SWKEY_STATE_IDLE) {
                        BTM_TRACE_API("Role Change is in progress for ACL handle 0x%04x", acl_handle);
                        p->state = SCO_ST_PEND_ROLECHANGE;

                    }
                }
            }

            if ( p->state != SCO_ST_PEND_UNPARK && p->state != SCO_ST_PEND_ROLECHANGE ) {
                if (is_orig) {
                    BTM_TRACE_API("BTM_CreateSco -> (e)SCO Link for ACL handle 0x%04x, Desired Type %d",
                                  acl_handle, btm_cb.sco_cb.desired_sco_mode);

                    if ((btm_send_connect_request(acl_handle, p_setup)) != BTM_CMD_STARTED) {
                        return (BTM_NO_RESOURCES);
                    }

                    p->state = SCO_ST_CONNECTING;
                } else {
                    p->state = SCO_ST_LISTENING;
                }
            }

            *p_sco_inx = xx;

            return (BTM_CMD_STARTED);
        }
    }

#endif
    /* If here, all SCO blocks in use */
    return (BTM_NO_RESOURCES);
}