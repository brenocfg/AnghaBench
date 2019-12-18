#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_17__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  int tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBTM_SP_KEYPRESS ;
struct TYPE_25__ {int /*<<< orphan*/  upgrade; int /*<<< orphan*/  bd_addr; } ;
struct TYPE_24__ {int /*<<< orphan*/  bd_addr; int /*<<< orphan*/ * bd_name; int /*<<< orphan*/  dev_class; } ;
struct TYPE_22__ {int status; int /*<<< orphan*/  r; int /*<<< orphan*/  c; } ;
struct TYPE_18__ {int /*<<< orphan*/ * bd_name; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  bd_addr; int /*<<< orphan*/  passkey; } ;
struct TYPE_29__ {int /*<<< orphan*/ * bd_name; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  bd_addr; int /*<<< orphan*/  rmt_io_caps; int /*<<< orphan*/  loc_io_caps; int /*<<< orphan*/  rmt_auth_req; int /*<<< orphan*/  loc_auth_req; int /*<<< orphan*/  just_works; } ;
struct TYPE_27__ {int /*<<< orphan*/  auth_req; int /*<<< orphan*/  oob_data; int /*<<< orphan*/  io_cap; int /*<<< orphan*/  bd_addr; } ;
struct TYPE_26__ {int /*<<< orphan*/  oob_data; int /*<<< orphan*/  auth_req; int /*<<< orphan*/  is_orig; int /*<<< orphan*/  io_cap; int /*<<< orphan*/  bd_addr; } ;
struct TYPE_19__ {TYPE_4__ upgrade; int /*<<< orphan*/  key_press; TYPE_3__ rmt_oob; TYPE_1__ loc_oob; TYPE_10__ key_notif; TYPE_8__ cfm_req; TYPE_6__ io_rsp; TYPE_5__ io_req; } ;
typedef  TYPE_11__ tBTM_SP_EVT_DATA ;
typedef  int tBTM_SP_EVT ;
typedef  void* tBTA_DM_SEC_EVT ;
struct TYPE_23__ {int /*<<< orphan*/ * bd_name; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  bd_addr; } ;
struct TYPE_30__ {int /*<<< orphan*/ * bd_name; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  bd_addr; int /*<<< orphan*/  passkey; } ;
struct TYPE_28__ {int /*<<< orphan*/  rmt_io_caps; int /*<<< orphan*/  loc_io_caps; int /*<<< orphan*/  rmt_auth_req; int /*<<< orphan*/  loc_auth_req; int /*<<< orphan*/  just_works; } ;
struct TYPE_20__ {int /*<<< orphan*/  key_press; TYPE_2__ rmt_oob; TYPE_9__ key_notif; TYPE_7__ cfm_req; } ;
typedef  TYPE_12__ tBTA_DM_SEC ;
typedef  int UINT8 ;
struct TYPE_21__ {void* pin_evt; int /*<<< orphan*/  (* p_sec_cback ) (void*,TYPE_12__*) ;int /*<<< orphan*/  pin_dev_class; int /*<<< orphan*/  pin_bd_addr; int /*<<< orphan*/  num_val; int /*<<< orphan*/  just_works; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BD_NAME ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_EVENT (char*,int,...) ; 
 int /*<<< orphan*/  APPL_TRACE_WARNING (char*) ; 
 int /*<<< orphan*/  BCM_STRNCPY_S (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BD_NAME_LEN ; 
 int /*<<< orphan*/  BTA_COPY_DEVICE_CLASS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* BTA_DM_SP_CFM_REQ_EVT ; 
 void* BTA_DM_SP_KEYPRESS_EVT ; 
 void* BTA_DM_SP_KEY_NOTIF_EVT ; 
 void* BTA_DM_SP_KEY_REQ_EVT ; 
 void* BTA_DM_SP_RMT_OOB_EVT ; 
 int BTM_CMD_STARTED ; 
 int BTM_NOT_AUTHORIZED ; 
 int BTM_ReadRemoteDeviceName (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  BTM_SP_CFM_REQ_EVT 137 
#define  BTM_SP_COMPLT_EVT 136 
#define  BTM_SP_IO_REQ_EVT 135 
#define  BTM_SP_IO_RSP_EVT 134 
#define  BTM_SP_KEYPRESS_EVT 133 
#define  BTM_SP_KEY_NOTIF_EVT 132 
#define  BTM_SP_KEY_REQ_EVT 131 
#define  BTM_SP_LOC_OOB_EVT 130 
#define  BTM_SP_RMT_OOB_EVT 129 
#define  BTM_SP_UPGRADE_EVT 128 
 int BTM_SUCCESS ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_17__ bta_dm_cb ; 
 int /*<<< orphan*/  bta_dm_co_io_req (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_dm_co_io_rsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_dm_co_lk_upgrade (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_dm_co_loc_oob (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_dm_co_rmt_oob (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_dm_pinname_cback ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (void*,TYPE_12__*) ; 
 int /*<<< orphan*/  stub2 (void*,TYPE_12__*) ; 
 int /*<<< orphan*/  stub3 (void*,TYPE_12__*) ; 

__attribute__((used)) static UINT8 bta_dm_sp_cback (tBTM_SP_EVT event, tBTM_SP_EVT_DATA *p_data)
{
    tBTM_STATUS status = BTM_CMD_STARTED;
    tBTA_DM_SEC sec_event;
    tBTA_DM_SEC_EVT pin_evt = BTA_DM_SP_KEY_NOTIF_EVT;

    APPL_TRACE_EVENT("bta_dm_sp_cback: %d", event);
    if (!bta_dm_cb.p_sec_cback) {
        return BTM_NOT_AUTHORIZED;
    }

    /* TODO_SP */
    switch (event) {
    case BTM_SP_IO_REQ_EVT:
#if (BT_SSP_INCLUDED == TRUE)
        /* translate auth_req */
        bta_dm_co_io_req(p_data->io_req.bd_addr, &p_data->io_req.io_cap,
                         &p_data->io_req.oob_data, &p_data->io_req.auth_req, p_data->io_req.is_orig);
#endif
#if BTM_OOB_INCLUDED == FALSE
        status = BTM_SUCCESS;
#endif

        APPL_TRACE_EVENT("io mitm: %d oob_data:%d", p_data->io_req.auth_req, p_data->io_req.oob_data);
        break;
    case BTM_SP_IO_RSP_EVT:
#if (BT_SSP_INCLUDED == TRUE)
        bta_dm_co_io_rsp(p_data->io_rsp.bd_addr, p_data->io_rsp.io_cap,
                         p_data->io_rsp.oob_data, p_data->io_rsp.auth_req );
#endif
        break;

    case BTM_SP_CFM_REQ_EVT:
        pin_evt = BTA_DM_SP_CFM_REQ_EVT;
        bta_dm_cb.just_works = sec_event.cfm_req.just_works = p_data->cfm_req.just_works;
        sec_event.cfm_req.loc_auth_req = p_data->cfm_req.loc_auth_req;
        sec_event.cfm_req.rmt_auth_req = p_data->cfm_req.rmt_auth_req;
        sec_event.cfm_req.loc_io_caps = p_data->cfm_req.loc_io_caps;
        sec_event.cfm_req.rmt_io_caps = p_data->cfm_req.rmt_io_caps;

        /* continue to next case */
#if (BT_SSP_INCLUDED == TRUE)
    /* Passkey entry mode, mobile device with output capability is very
        unlikely to receive key request, so skip this event */
    case BTM_SP_KEY_REQ_EVT:
    case BTM_SP_KEY_NOTIF_EVT:
#endif
        if (BTM_SP_CFM_REQ_EVT == event) {
            /* Due to the switch case falling through below to BTM_SP_KEY_NOTIF_EVT,
               call remote name request using values from cfm_req */
            if (p_data->cfm_req.bd_name[0] == 0) {
                bta_dm_cb.pin_evt = pin_evt;
                bdcpy(bta_dm_cb.pin_bd_addr, p_data->cfm_req.bd_addr);
                BTA_COPY_DEVICE_CLASS(bta_dm_cb.pin_dev_class, p_data->cfm_req.dev_class);
                if ((BTM_ReadRemoteDeviceName(p_data->cfm_req.bd_addr, bta_dm_pinname_cback,
                                              BT_TRANSPORT_BR_EDR)) == BTM_CMD_STARTED) {
                    return BTM_CMD_STARTED;
                }
                APPL_TRACE_WARNING(" bta_dm_sp_cback() -> Failed to start Remote Name Request  ");
            } else {
                /* Due to the switch case falling through below to BTM_SP_KEY_NOTIF_EVT,
                   copy these values into key_notif from cfm_req */
                bdcpy(sec_event.key_notif.bd_addr, p_data->cfm_req.bd_addr);
                BTA_COPY_DEVICE_CLASS(sec_event.key_notif.dev_class, p_data->cfm_req.dev_class);
                BCM_STRNCPY_S((char *)sec_event.key_notif.bd_name, sizeof(BD_NAME),
                              (char *)p_data->cfm_req.bd_name, (BD_NAME_LEN - 1));
                sec_event.key_notif.bd_name[BD_NAME_LEN - 1] = 0;
            }
        }

        bta_dm_cb.num_val = sec_event.key_notif.passkey = p_data->key_notif.passkey;
        if (BTM_SP_KEY_NOTIF_EVT == event) {
            /* If the device name is not known, save bdaddr and devclass
               and initiate a name request with values from key_notif */
            if (p_data->key_notif.bd_name[0] == 0) {
                bta_dm_cb.pin_evt = pin_evt;
                bdcpy(bta_dm_cb.pin_bd_addr, p_data->key_notif.bd_addr);
                BTA_COPY_DEVICE_CLASS(bta_dm_cb.pin_dev_class, p_data->key_notif.dev_class);
                if ((BTM_ReadRemoteDeviceName(p_data->key_notif.bd_addr, bta_dm_pinname_cback,
                                              BT_TRANSPORT_BR_EDR)) == BTM_CMD_STARTED) {
                    return BTM_CMD_STARTED;
                }
                APPL_TRACE_WARNING(" bta_dm_sp_cback() -> Failed to start Remote Name Request  ");
            } else {
                bdcpy(sec_event.key_notif.bd_addr, p_data->key_notif.bd_addr);
                BTA_COPY_DEVICE_CLASS(sec_event.key_notif.dev_class, p_data->key_notif.dev_class);
                BCM_STRNCPY_S((char *)sec_event.key_notif.bd_name, sizeof(BD_NAME),
                              (char *)p_data->key_notif.bd_name, (BD_NAME_LEN - 1));
                sec_event.key_notif.bd_name[BD_NAME_LEN - 1] = 0;
            }
        }

        if (BTM_SP_KEY_REQ_EVT == event) {
            pin_evt = BTA_DM_SP_KEY_REQ_EVT;
            /* If the device name is not known, save bdaddr and devclass
               and initiate a name request with values from key_notif */
            if (p_data->key_notif.bd_name[0] == 0) {
                bta_dm_cb.pin_evt = pin_evt;
                bdcpy(bta_dm_cb.pin_bd_addr, p_data->key_notif.bd_addr);
                BTA_COPY_DEVICE_CLASS(bta_dm_cb.pin_dev_class, p_data->key_notif.dev_class);
                if ((BTM_ReadRemoteDeviceName(p_data->key_notif.bd_addr, bta_dm_pinname_cback,
                                              BT_TRANSPORT_BR_EDR)) == BTM_CMD_STARTED) {
                    return BTM_CMD_STARTED;
                }
                APPL_TRACE_WARNING(" bta_dm_sp_cback() -> Failed to start Remote Name Request  ");
            } else {
                bdcpy(sec_event.key_notif.bd_addr, p_data->key_notif.bd_addr);
                BTA_COPY_DEVICE_CLASS(sec_event.key_notif.dev_class, p_data->key_notif.dev_class);
                BCM_STRNCPY_S((char *)sec_event.key_notif.bd_name, sizeof(BD_NAME),
                              (char *)p_data->key_notif.bd_name, (BD_NAME_LEN - 1));
                sec_event.key_notif.bd_name[BD_NAME_LEN - 1] = 0;
            }
        }
        bta_dm_cb.p_sec_cback(pin_evt, &sec_event);

        break;

#if BTM_OOB_INCLUDED == TRUE
    case BTM_SP_LOC_OOB_EVT:
        bta_dm_co_loc_oob((BOOLEAN)(p_data->loc_oob.status == BTM_SUCCESS),
                          p_data->loc_oob.c, p_data->loc_oob.r);
        break;

    case BTM_SP_RMT_OOB_EVT:
        /* If the device name is not known, save bdaddr and devclass and initiate a name request */
        if (p_data->rmt_oob.bd_name[0] == 0) {
            bta_dm_cb.pin_evt = BTA_DM_SP_RMT_OOB_EVT;
            bdcpy(bta_dm_cb.pin_bd_addr, p_data->rmt_oob.bd_addr);
            BTA_COPY_DEVICE_CLASS(bta_dm_cb.pin_dev_class, p_data->rmt_oob.dev_class);
            if ((BTM_ReadRemoteDeviceName(p_data->rmt_oob.bd_addr, bta_dm_pinname_cback,
                                          BT_TRANSPORT_BR_EDR)) == BTM_CMD_STARTED) {
                return BTM_CMD_STARTED;
            }
            APPL_TRACE_WARNING(" bta_dm_sp_cback() -> Failed to start Remote Name Request  ");
        }

        bdcpy(sec_event.rmt_oob.bd_addr, p_data->rmt_oob.bd_addr);
        BTA_COPY_DEVICE_CLASS(sec_event.rmt_oob.dev_class, p_data->rmt_oob.dev_class);
        BCM_STRNCPY_S((char *)sec_event.rmt_oob.bd_name, sizeof(BD_NAME), (char *)p_data->rmt_oob.bd_name, (BD_NAME_LEN - 1));
        sec_event.rmt_oob.bd_name[BD_NAME_LEN - 1] = 0;

        bta_dm_cb.p_sec_cback(BTA_DM_SP_RMT_OOB_EVT, &sec_event);

        bta_dm_co_rmt_oob(p_data->rmt_oob.bd_addr);
        break;
#endif
    case BTM_SP_COMPLT_EVT:
        /* do not report this event - handled by link_key_callback or auth_complete_callback */
        break;

    case BTM_SP_KEYPRESS_EVT:
        memcpy(&sec_event.key_press, &p_data->key_press, sizeof(tBTM_SP_KEYPRESS));
        bta_dm_cb.p_sec_cback(BTA_DM_SP_KEYPRESS_EVT, &sec_event);
        break;

    case BTM_SP_UPGRADE_EVT:
        bta_dm_co_lk_upgrade(p_data->upgrade.bd_addr, &p_data->upgrade.upgrade );
        break;

    default:
        status = BTM_NOT_AUTHORIZED;
        break;
    }
    APPL_TRACE_EVENT("dm status: %d", status);
    return status;
}