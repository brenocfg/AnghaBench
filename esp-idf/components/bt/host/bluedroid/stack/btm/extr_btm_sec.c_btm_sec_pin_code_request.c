#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int* dev_class; TYPE_3__* p_cur_service; int /*<<< orphan*/  sec_bd_name; int /*<<< orphan*/  is_originator; int /*<<< orphan*/  trusted_mask; int /*<<< orphan*/  sm4; } ;
typedef  TYPE_4__ tBTM_SEC_DEV_REC ;
struct TYPE_11__ {int /*<<< orphan*/  (* p_pin_callback ) (int*,int*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_15__ {int member_0; int member_1; int member_2; int member_3; } ;
struct TYPE_10__ {scalar_t__ pin_type; int pin_code_len; TYPE_6__ pin_code; } ;
struct TYPE_14__ {scalar_t__ pairing_state; int* pairing_bda; int pin_code_len_saved; int* connecting_bda; int* connecting_dc; scalar_t__ pin_code_len; TYPE_2__ api; int /*<<< orphan*/  pairing_flags; scalar_t__ pairing_disabled; TYPE_6__ pin_code; TYPE_1__ cfg; } ;
typedef  TYPE_5__ tBTM_CB ;
typedef  int UINT8 ;
struct TYPE_12__ {int security_flags; } ;
typedef  TYPE_6__ PIN_CODE ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int BTM_COD_MAJOR_CLASS_MASK ; 
 int BTM_COD_MAJOR_PERIPHERAL ; 
 int BTM_COD_MINOR_KEYBOARD ; 
 int /*<<< orphan*/  BTM_PAIR_FLAGS_PEER_STARTED_DD ; 
 int /*<<< orphan*/  BTM_PAIR_FLAGS_PIN_REQD ; 
 scalar_t__ BTM_PAIR_STATE_IDLE ; 
 scalar_t__ BTM_PAIR_STATE_WAIT_AUTH_COMPLETE ; 
 scalar_t__ BTM_PAIR_STATE_WAIT_LOCAL_PIN ; 
 scalar_t__ BTM_PAIR_STATE_WAIT_PIN_REQ ; 
 int /*<<< orphan*/  BTM_SEC_CLR_TRUSTED_DEVICE (int /*<<< orphan*/ ) ; 
 int BTM_SEC_IN_MIN_16_DIGIT_PIN ; 
 int /*<<< orphan*/  BTM_SM4_KNOWN ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*,...) ; 
 int /*<<< orphan*/  BTM_TRACE_WARNING (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  DEV_CLASS_LEN ; 
 int FALSE ; 
 scalar_t__ HCI_PIN_TYPE_FIXED ; 
 TYPE_5__ btm_cb ; 
 TYPE_4__* btm_find_or_alloc_dev (int*) ; 
 int /*<<< orphan*/  btm_pair_state_descr (scalar_t__) ; 
 int /*<<< orphan*/  btm_sec_change_pairing_state (scalar_t__) ; 
 int /*<<< orphan*/  btsnd_hcic_pin_code_neg_reply (int*) ; 
 int /*<<< orphan*/  btsnd_hcic_pin_code_req_reply (int*,int,TYPE_6__) ; 
 scalar_t__ memcmp (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int*,int*,int /*<<< orphan*/ ,int) ; 

void btm_sec_pin_code_request (UINT8 *p_bda)
{
    tBTM_SEC_DEV_REC *p_dev_rec;
    tBTM_CB          *p_cb = &btm_cb;

#ifdef PORCHE_PAIRING_CONFLICT
    UINT8 default_pin_code_len = 4;
    PIN_CODE default_pin_code = {0x30, 0x30, 0x30, 0x30};
#endif
#if (BT_USE_TRACES == TRUE && SMP_INCLUDED == TRUE)
    BTM_TRACE_EVENT ("btm_sec_pin_code_request()  State: %s, BDA:%04x%08x\n",
                     btm_pair_state_descr(btm_cb.pairing_state),
                     (p_bda[0] << 8) + p_bda[1], (p_bda[2] << 24) + (p_bda[3] << 16) + (p_bda[4] << 8) + p_bda[5] );
#endif  ///BT_USE_TRACES == TRUE && SMP_INCLUDED == TRUE
    if (btm_cb.pairing_state != BTM_PAIR_STATE_IDLE) {
        if ( (memcmp (p_bda, btm_cb.pairing_bda, BD_ADDR_LEN) == 0)  &&
                (btm_cb.pairing_state == BTM_PAIR_STATE_WAIT_AUTH_COMPLETE) ) {
            /* fake this out - porshe carkit issue - */
//            btm_cb.pairing_state = BTM_PAIR_STATE_IDLE;
            if (! btm_cb.pin_code_len_saved) {
                btsnd_hcic_pin_code_neg_reply (p_bda);
                return;
            } else {
                btsnd_hcic_pin_code_req_reply (p_bda, btm_cb.pin_code_len_saved, p_cb->pin_code);
                return;
            }
        } else if ((btm_cb.pairing_state != BTM_PAIR_STATE_WAIT_PIN_REQ)
                   || memcmp (p_bda, btm_cb.pairing_bda, BD_ADDR_LEN) != 0) {
#if (BT_USE_TRACES == TRUE && SMP_INCLUDED == TRUE)
            BTM_TRACE_WARNING ("btm_sec_pin_code_request() rejected - state: %s\n",
                               btm_pair_state_descr(btm_cb.pairing_state));
#endif  ///BT_USE_TRACES == TRUE && SMP_INCLUDED == TRUE
#ifdef PORCHE_PAIRING_CONFLICT
            /* reply pin code again due to counter in_rand when local initiates pairing */
            BTM_TRACE_EVENT ("btm_sec_pin_code_request from remote dev. for local initiated pairing\n");
            if (! btm_cb.pin_code_len_saved) {
                btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_AUTH_COMPLETE);
                btsnd_hcic_pin_code_req_reply (p_bda, default_pin_code_len, default_pin_code);
            } else {
                btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_AUTH_COMPLETE);
                btsnd_hcic_pin_code_req_reply (p_bda, btm_cb.pin_code_len_saved, p_cb->pin_code);
            }
#else
            btsnd_hcic_pin_code_neg_reply (p_bda);
#endif
            return;
        }
    }

    p_dev_rec = btm_find_or_alloc_dev (p_bda);
    /* received PIN code request. must be non-sm4 */
    p_dev_rec->sm4 = BTM_SM4_KNOWN;

    if (btm_cb.pairing_state == BTM_PAIR_STATE_IDLE) {
        memcpy (btm_cb.pairing_bda, p_bda, BD_ADDR_LEN);

        btm_cb.pairing_flags = BTM_PAIR_FLAGS_PEER_STARTED_DD;
        /* Make sure we reset the trusted mask to help against attacks */
        BTM_SEC_CLR_TRUSTED_DEVICE(p_dev_rec->trusted_mask);
    }

    if (!p_cb->pairing_disabled && (p_cb->cfg.pin_type == HCI_PIN_TYPE_FIXED)) {
        BTM_TRACE_EVENT ("btm_sec_pin_code_request fixed pin replying\n");
        btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_AUTH_COMPLETE);
        btsnd_hcic_pin_code_req_reply (p_bda, p_cb->cfg.pin_code_len, p_cb->cfg.pin_code);
        return;
    }

    /* Use the connecting device's CoD for the connection */
    if ( (!memcmp (p_bda, p_cb->connecting_bda, BD_ADDR_LEN))
            &&  (p_cb->connecting_dc[0] || p_cb->connecting_dc[1] || p_cb->connecting_dc[2]) ) {
        memcpy (p_dev_rec->dev_class, p_cb->connecting_dc, DEV_CLASS_LEN);
    }

    /* We could have started connection after asking user for the PIN code */
    if (btm_cb.pin_code_len != 0) {
        BTM_TRACE_EVENT ("btm_sec_pin_code_request bonding sending reply\n");
        btsnd_hcic_pin_code_req_reply (p_bda, btm_cb.pin_code_len, p_cb->pin_code);

#ifdef PORCHE_PAIRING_CONFLICT
        btm_cb.pin_code_len_saved = btm_cb.pin_code_len;
#endif

        /* Mark that we forwarded received from the user PIN code */
        btm_cb.pin_code_len = 0;

        /* We can change mode back right away, that other connection being established */
        /* is not forced to be secure - found a FW issue, so we can not do this
        btm_restore_mode(); */

        btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_AUTH_COMPLETE);
    }

    /* If pairing disabled OR (no PIN callback and not bonding) */
    /* OR we could not allocate entry in the database reject pairing request */
    else if (p_cb->pairing_disabled
             || (p_cb->api.p_pin_callback == NULL)

             /* OR Microsoft keyboard can for some reason try to establish connection */
             /*  the only thing we can do here is to shut it up.  Normally we will be originator */
             /*  for keyboard bonding */
             || (!p_dev_rec->is_originator
                 && ((p_dev_rec->dev_class[1] & BTM_COD_MAJOR_CLASS_MASK) == BTM_COD_MAJOR_PERIPHERAL)
                 &&  (p_dev_rec->dev_class[2] & BTM_COD_MINOR_KEYBOARD)) ) {
        BTM_TRACE_WARNING("btm_sec_pin_code_request(): Pairing disabled:%d; PIN callback:%p, Dev Rec:%p!\n",
                          p_cb->pairing_disabled, p_cb->api.p_pin_callback, p_dev_rec);

        btsnd_hcic_pin_code_neg_reply (p_bda);
    }
    /* Notify upper layer of PIN request and start expiration timer */
    else {
        btm_cb.pin_code_len_saved = 0;
        btm_sec_change_pairing_state (BTM_PAIR_STATE_WAIT_LOCAL_PIN);
        /* Pin code request can not come at the same time as connection request */
        memcpy (p_cb->connecting_bda, p_bda, BD_ADDR_LEN);
        memcpy (p_cb->connecting_dc,  p_dev_rec->dev_class, DEV_CLASS_LEN);

        BTM_TRACE_EVENT ("btm_sec_pin_code_request going for callback\n");
        btm_cb.pairing_flags |= BTM_PAIR_FLAGS_PIN_REQD;
        if (p_cb->api.p_pin_callback) {
            (*p_cb->api.p_pin_callback) (p_bda, p_dev_rec->dev_class, p_dev_rec->sec_bd_name,
                                         (p_dev_rec->p_cur_service == NULL) ? FALSE
                                         : (p_dev_rec->p_cur_service->security_flags
                                            & BTM_SEC_IN_MIN_16_DIGIT_PIN));
        }
    }
    return;
}