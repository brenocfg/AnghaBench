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
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct video_viewport {scalar_t__ full_height; scalar_t__ full_width; scalar_t__ height; scalar_t__ width; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_7__ {int updated; int /*<<< orphan*/  lock; scalar_t__* msg; int /*<<< orphan*/  pitch; int /*<<< orphan*/  count; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  buffer; } ;
struct TYPE_8__ {scalar_t__ send_cmd; int alive; int focus; int has_windowed; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond_cmd; struct video_viewport vp; TYPE_2__ frame; int /*<<< orphan*/  driver_data; TYPE_1__* driver; int /*<<< orphan*/  cmd_data; int /*<<< orphan*/  cond_thread; } ;
typedef  TYPE_3__ thread_video_t ;
typedef  int /*<<< orphan*/  thread_packet_t ;
struct TYPE_6__ {int (* frame ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* viewport_info ) (int /*<<< orphan*/ ,struct video_viewport*) ;scalar_t__ (* has_windowed ) (int /*<<< orphan*/ ) ;scalar_t__ (* focus ) (int /*<<< orphan*/ ) ;scalar_t__ (* alive ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ CMD_VIDEO_NONE ; 
 int /*<<< orphan*/  scond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,struct video_viewport*) ; 
 int /*<<< orphan*/  thread_update_driver_state (TYPE_3__*) ; 
 int /*<<< orphan*/  video_driver_build_info (int /*<<< orphan*/ *) ; 
 scalar_t__ video_thread_handle_packet (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void video_thread_loop(void *data)
{
   thread_video_t *thr = (thread_video_t*)data;

   for (;;)
   {
      thread_packet_t pkt;
      bool updated = false;

      slock_lock(thr->lock);
      while (thr->send_cmd == CMD_VIDEO_NONE && !thr->frame.updated)
         scond_wait(thr->cond_thread, thr->lock);
      if (thr->frame.updated)
         updated = true;

      /* To avoid race condition where send_cmd is updated
       * right after the switch is checked. */
      pkt = thr->cmd_data;

      slock_unlock(thr->lock);

      if (video_thread_handle_packet(thr, &pkt))
         return;

      if (updated)
      {
         struct video_viewport vp;
         bool                 ret = false;
         bool               alive = false;
         bool               focus = false;
         bool        has_windowed = true;

         vp.x                     = 0;
         vp.y                     = 0;
         vp.width                 = 0;
         vp.height                = 0;
         vp.full_width            = 0;
         vp.full_height           = 0;

         slock_lock(thr->frame.lock);

         thread_update_driver_state(thr);

         if (thr->driver && thr->driver->frame)
         {
            video_frame_info_t video_info;
            video_driver_build_info(&video_info);

            ret = thr->driver->frame(thr->driver_data,
                  thr->frame.buffer, thr->frame.width, thr->frame.height,
                  thr->frame.count,
                  thr->frame.pitch, *thr->frame.msg ? thr->frame.msg : NULL,
                  &video_info);
         }

         slock_unlock(thr->frame.lock);

         if (thr->driver && thr->driver->alive)
            alive = ret && thr->driver->alive(thr->driver_data);

         if (thr->driver && thr->driver->focus)
            focus = ret && thr->driver->focus(thr->driver_data);

         if (thr->driver && thr->driver->has_windowed)
            has_windowed = ret && thr->driver->has_windowed(thr->driver_data);

         if (thr->driver && thr->driver->viewport_info)
            thr->driver->viewport_info(thr->driver_data, &vp);

         slock_lock(thr->lock);
         thr->alive         = alive;
         thr->focus         = focus;
         thr->has_windowed  = has_windowed;
         thr->frame.updated = false;
         thr->vp            = vp;
         scond_signal(thr->cond_cmd);
         slock_unlock(thr->lock);
      }
   }
}