#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fixed_queue_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* fragment_and_dispatch ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  FIXED_QUEUE_MAX_TIMEOUT ; 
 scalar_t__ fixed_queue_dequeue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* packet_fragmenter ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void event_packet_ready(fixed_queue_t *queue)
{
    BT_HDR *packet = (BT_HDR *)fixed_queue_dequeue(queue, FIXED_QUEUE_MAX_TIMEOUT);
    // The queue may be the command queue or the packet queue, we don't care

    packet_fragmenter->fragment_and_dispatch(packet);
}