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
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cond_cmd; int /*<<< orphan*/  send_cmd; int /*<<< orphan*/  reply_cmd; TYPE_2__ cmd_data; } ;
typedef  TYPE_1__ thread_video_t ;
typedef  TYPE_2__ thread_packet_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_VIDEO_NONE ; 
 int /*<<< orphan*/  scond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void video_thread_reply(thread_video_t *thr, const thread_packet_t *pkt)
{
   slock_lock(thr->lock);

   thr->cmd_data  = *pkt;

   thr->reply_cmd = pkt->type;
   thr->send_cmd  = CMD_VIDEO_NONE;

   scond_signal(thr->cond_cmd);
   slock_unlock(thr->lock);
}