#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_3__ {int /*<<< orphan*/  layer_specific; scalar_t__ offset; scalar_t__ len; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTU_HCI_RCV_MBOX ; 
 int /*<<< orphan*/  BTU_TASK ; 
 int /*<<< orphan*/  BT_EVT_TO_GAP_MSG ; 
 int /*<<< orphan*/  BT_HDR_SIZE ; 
 int /*<<< orphan*/  GAP_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  GKI_send_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ osi_malloc (int /*<<< orphan*/ ) ; 

void gap_send_event (UINT16 gap_handle)
{
    BT_HDR  *p_msg;

    if ((p_msg = (BT_HDR *)osi_malloc(BT_HDR_SIZE)) != NULL) {
        p_msg->event  = BT_EVT_TO_GAP_MSG;
        p_msg->len    = 0;
        p_msg->offset = 0;
        p_msg->layer_specific = gap_handle;

        GKI_send_msg(BTU_TASK, BTU_HCI_RCV_MBOX, p_msg);
    } else {
        GAP_TRACE_ERROR("Unable to allocate message buffer for event.");
    }
}