#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  thread_video_t ;
typedef  int /*<<< orphan*/  thread_packet_t ;

/* Variables and functions */
 int /*<<< orphan*/  video_thread_send_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_thread_wait_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void video_thread_send_and_wait_user_to_thread(thread_video_t *thr, thread_packet_t *pkt)
{
   video_thread_send_packet(thr, pkt);
   video_thread_wait_reply(thr, pkt);
}