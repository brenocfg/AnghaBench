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
struct TYPE_6__ {TYPE_1__* p_lcb; } ;
typedef  TYPE_2__ tL2C_CCB ;
struct TYPE_5__ {int /*<<< orphan*/  ucd_out_sec_pending_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIXED_QUEUE_MAX_TIMEOUT ; 
 int /*<<< orphan*/  fixed_queue_enqueue (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cu_check_channel_congestion (TYPE_2__*) ; 

void l2c_ucd_enqueue_pending_out_sec_q(tL2C_CCB  *p_ccb, void *p_data)
{
    fixed_queue_enqueue(p_ccb->p_lcb->ucd_out_sec_pending_q, p_data, FIXED_QUEUE_MAX_TIMEOUT);
    l2cu_check_channel_congestion (p_ccb);
}