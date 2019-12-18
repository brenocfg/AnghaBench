#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_video_t ;
struct TYPE_4__ {unsigned int i; } ;
struct TYPE_5__ {TYPE_1__ data; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ thread_packet_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SET_ROTATION ; 
 int /*<<< orphan*/  video_thread_send_and_wait_user_to_thread (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void video_thread_set_rotation(void *data, unsigned rotation)
{
   thread_video_t *thr = (thread_video_t*)data;
   thread_packet_t pkt = { CMD_SET_ROTATION };

   if (!thr)
      return;

   pkt.data.i = rotation;

   video_thread_send_and_wait_user_to_thread(thr, &pkt);
}