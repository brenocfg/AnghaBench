#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_15__ {int /*<<< orphan*/  (* callback ) (TYPE_3__*) ;} ;
typedef  TYPE_2__ post_to_task_hack_t ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_16__ {int event; int /*<<< orphan*/ * data; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* event_cb ) (TYPE_3__*) ;int /*<<< orphan*/  event_range; } ;
struct TYPE_13__ {TYPE_1__* event_reg; } ;
typedef  TYPE_3__ BT_HDR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int BTU_MAX_REG_EVENT ; 
#define  BTU_POST_TO_TASK_NO_GOOD_HORRIBLE_HACK 133 
 int BT_EVT_MASK ; 
#define  BT_EVT_TO_BTU_HCI_ACL 132 
#define  BT_EVT_TO_BTU_HCI_CMD 131 
#define  BT_EVT_TO_BTU_HCI_EVT 130 
#define  BT_EVT_TO_BTU_HCI_SCO 129 
#define  BT_EVT_TO_BTU_L2C_SEG_XMIT 128 
 int BT_SUB_EVT_MASK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  btm_route_sco_data (TYPE_3__*) ; 
 TYPE_11__ btu_cb ; 
 int /*<<< orphan*/  btu_check_bt_sleep () ; 
 int /*<<< orphan*/  btu_hcif_process_event (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  btu_hcif_send_cmd (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  l2c_link_segments_xmitted (TYPE_3__*) ; 
 int /*<<< orphan*/  l2c_rcv_acl_data (TYPE_3__*) ; 
 int /*<<< orphan*/  osi_free (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 

__attribute__((used)) static void btu_hci_msg_process(void *param)
{
    /* Determine the input message type. */
    BT_HDR *p_msg = (BT_HDR *)param;

    switch (p_msg->event & BT_EVT_MASK) {
    case BTU_POST_TO_TASK_NO_GOOD_HORRIBLE_HACK: // TODO(zachoverflow): remove this
      {
        post_to_task_hack_t *ph = (post_to_task_hack_t *) &p_msg->data[0];
        ph->callback(p_msg);
        break;
      }
    case BT_EVT_TO_BTU_HCI_ACL:
        /* All Acl Data goes to L2CAP */
        l2c_rcv_acl_data (p_msg);
        break;

    case BT_EVT_TO_BTU_L2C_SEG_XMIT:
        /* L2CAP segment transmit complete */
        l2c_link_segments_xmitted (p_msg);
        break;

    case BT_EVT_TO_BTU_HCI_SCO:
#if BTM_SCO_INCLUDED == TRUE
        btm_route_sco_data (p_msg);
        osi_free(p_msg);
        break;
#endif

    case BT_EVT_TO_BTU_HCI_EVT:
        btu_hcif_process_event ((UINT8)(p_msg->event & BT_SUB_EVT_MASK), p_msg);
        osi_free(p_msg);

#if (defined(HCILP_INCLUDED) && HCILP_INCLUDED == TRUE)
        /* If host receives events which it doesn't response to, */
        /* host should start idle timer to enter sleep mode.     */
        btu_check_bt_sleep ();
#endif
        break;

    case BT_EVT_TO_BTU_HCI_CMD:
        btu_hcif_send_cmd ((UINT8)(p_msg->event & BT_SUB_EVT_MASK), p_msg);
        break;

    default:;
        int i = 0;
        uint16_t mask = (UINT16) (p_msg->event & BT_EVT_MASK);
        BOOLEAN handled = FALSE;

        for (; !handled && i < BTU_MAX_REG_EVENT; i++) {
            if (btu_cb.event_reg[i].event_cb == NULL) {
                continue;
            }

            if (mask == btu_cb.event_reg[i].event_range) {
                if (btu_cb.event_reg[i].event_cb) {
                    btu_cb.event_reg[i].event_cb(p_msg);
                    handled = TRUE;
                }
            }
        }

        if (handled == FALSE) {
            osi_free (p_msg);
        }

        break;
    }

}