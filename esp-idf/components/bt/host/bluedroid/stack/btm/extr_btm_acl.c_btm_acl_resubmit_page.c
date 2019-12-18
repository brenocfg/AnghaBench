#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dev_class; int /*<<< orphan*/  bd_addr; } ;
typedef  TYPE_1__ tBTM_SEC_DEV_REC ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_8__ {int /*<<< orphan*/  paging; int /*<<< orphan*/  connecting_dc; int /*<<< orphan*/  connecting_bda; int /*<<< orphan*/  page_queue; } ;
struct TYPE_7__ {int offset; } ;
typedef  TYPE_2__ BT_HDR ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  DEV_CLASS_LEN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LOCAL_BR_EDR_CONTROLLER_ID ; 
 int /*<<< orphan*/  STREAM_TO_BDADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__ btm_cb ; 
 TYPE_1__* btm_find_or_alloc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_hcif_send_cmd (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ fixed_queue_dequeue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void btm_acl_resubmit_page (void)
{
#if (SMP_INCLUDED == TRUE)
    tBTM_SEC_DEV_REC *p_dev_rec;
    BT_HDR  *p_buf;
    UINT8   *pp;
    BD_ADDR bda;
    BTM_TRACE_DEBUG ("btm_acl_resubmit_page\n");
    /* If there were other page request schedule can start the next one */
    if ((p_buf = (BT_HDR *)fixed_queue_dequeue(btm_cb.page_queue, 0)) != NULL) {
        /* skip 3 (2 bytes opcode and 1 byte len) to get to the bd_addr
         * for both create_conn and rmt_name */
        pp = (UINT8 *)(p_buf + 1) + p_buf->offset + 3;

        STREAM_TO_BDADDR (bda, pp);

        p_dev_rec = btm_find_or_alloc_dev (bda);

        memcpy (btm_cb.connecting_bda, p_dev_rec->bd_addr,   BD_ADDR_LEN);
        memcpy (btm_cb.connecting_dc,  p_dev_rec->dev_class, DEV_CLASS_LEN);

        btu_hcif_send_cmd (LOCAL_BR_EDR_CONTROLLER_ID, p_buf);
    } else {
        btm_cb.paging = FALSE;
    }
#endif  ///SMP_INCLUDED == TRUE
}