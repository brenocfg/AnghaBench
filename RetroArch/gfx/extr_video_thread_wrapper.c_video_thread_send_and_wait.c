#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* send_and_wait ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ thread_video_t ;
typedef  int /*<<< orphan*/  thread_packet_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void video_thread_send_and_wait(thread_video_t *thr,
      thread_packet_t *pkt)
{
   if (!thr || !pkt)
      return;
   thr->send_and_wait(thr, pkt);
}