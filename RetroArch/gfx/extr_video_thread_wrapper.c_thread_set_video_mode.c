#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_video_t ;
struct TYPE_5__ {unsigned int width; unsigned int height; int fullscreen; } ;
struct TYPE_6__ {TYPE_1__ new_mode; } ;
struct TYPE_7__ {TYPE_2__ data; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ thread_packet_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_POKE_SET_VIDEO_MODE ; 
 int /*<<< orphan*/  video_thread_send_and_wait_user_to_thread (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static void thread_set_video_mode(void *data, unsigned width, unsigned height,
      bool video_fullscreen)
{
   thread_video_t *thr = (thread_video_t*)data;
   thread_packet_t pkt = { CMD_POKE_SET_VIDEO_MODE };

   if (!thr)
      return;

   pkt.data.new_mode.width      = width;
   pkt.data.new_mode.height     = height;
   pkt.data.new_mode.fullscreen = video_fullscreen;

   video_thread_send_and_wait_user_to_thread(thr, &pkt);
}