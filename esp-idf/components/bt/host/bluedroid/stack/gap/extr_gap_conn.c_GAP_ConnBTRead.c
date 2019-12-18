#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  rx_queue_size; int /*<<< orphan*/  rx_queue; } ;
typedef  TYPE_1__ tGAP_CCB ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_6__ {scalar_t__ len; } ;
typedef  TYPE_2__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  BT_PASS ; 
 int /*<<< orphan*/  GAP_ERR_BAD_HANDLE ; 
 int /*<<< orphan*/  GAP_NO_DATA_AVAIL ; 
 scalar_t__ fixed_queue_dequeue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* gap_find_ccb_by_handle (int /*<<< orphan*/ ) ; 

UINT16 GAP_ConnBTRead (UINT16 gap_handle, BT_HDR **pp_buf)
{
    tGAP_CCB    *p_ccb = gap_find_ccb_by_handle (gap_handle);
    BT_HDR      *p_buf;

    if (!p_ccb) {
        return (GAP_ERR_BAD_HANDLE);
    }

    p_buf = (BT_HDR *)fixed_queue_dequeue(p_ccb->rx_queue, 0);

    if (p_buf) {
        *pp_buf = p_buf;

        p_ccb->rx_queue_size -= p_buf->len;
        return (BT_PASS);
    } else {
        *pp_buf = NULL;
        return (GAP_NO_DATA_AVAIL);
    }
}