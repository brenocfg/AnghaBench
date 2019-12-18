#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int alive; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ thread_video_t ;
struct TYPE_6__ {int b; } ;
struct TYPE_8__ {TYPE_1__ data; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ thread_packet_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ALIVE ; 
 int /*<<< orphan*/  RARCH_CTL_IS_PAUSED ; 
 scalar_t__ rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_thread_send_and_wait_user_to_thread (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static bool video_thread_alive(void *data)
{
   bool ret;
   thread_video_t *thr = (thread_video_t*)data;

   if (rarch_ctl(RARCH_CTL_IS_PAUSED, NULL))
   {
      thread_packet_t pkt = { CMD_ALIVE };

      video_thread_send_and_wait_user_to_thread(thr, &pkt);
      return pkt.data.b;
   }

   slock_lock(thr->lock);
   ret = thr->alive;
   slock_unlock(thr->lock);

   return ret;
}