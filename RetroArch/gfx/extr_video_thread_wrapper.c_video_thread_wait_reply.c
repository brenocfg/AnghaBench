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
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_5__ {scalar_t__ reply_cmd; int /*<<< orphan*/  lock; TYPE_2__ cmd_data; int /*<<< orphan*/  cond_cmd; } ;
typedef  TYPE_1__ thread_video_t ;
typedef  TYPE_2__ thread_packet_t ;

/* Variables and functions */
 scalar_t__ CMD_VIDEO_NONE ; 
 int /*<<< orphan*/  scond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void video_thread_wait_reply(thread_video_t *thr, thread_packet_t *pkt)
{
   slock_lock(thr->lock);

   while (pkt->type != thr->reply_cmd)
      scond_wait(thr->cond_cmd, thr->lock);

   *pkt               = thr->cmd_data;
   thr->cmd_data.type = CMD_VIDEO_NONE;

   slock_unlock(thr->lock);
}