#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int frame_updated; int /*<<< orphan*/  full_screen; int /*<<< orphan*/  enable; int /*<<< orphan*/  alpha; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  rgb32; int /*<<< orphan*/  frame; } ;
struct TYPE_9__ {int alpha_update; unsigned int alpha_mods; int apply_state_changes; int /*<<< orphan*/  driver_data; TYPE_3__* poke; int /*<<< orphan*/  alpha_lock; int /*<<< orphan*/ * alpha_mod; TYPE_2__* overlay; TYPE_1__ texture; } ;
typedef  TYPE_4__ thread_video_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* apply_state_changes ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_texture_enable ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_texture_frame ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  (* set_alpha ) (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void thread_update_driver_state(thread_video_t *thr)
{
#if defined(HAVE_MENU)
   if (thr->texture.frame_updated)
   {
      if (thr->poke && thr->poke->set_texture_frame)
         thr->poke->set_texture_frame(thr->driver_data,
               thr->texture.frame, thr->texture.rgb32,
               thr->texture.width, thr->texture.height,
               thr->texture.alpha);
      thr->texture.frame_updated = false;
   }

   if (thr->poke && thr->poke->set_texture_enable)
      thr->poke->set_texture_enable(thr->driver_data,
            thr->texture.enable, thr->texture.full_screen);
#endif

#if defined(HAVE_OVERLAY)
   slock_lock(thr->alpha_lock);
   if (thr->alpha_update)
   {
      unsigned i;
      for (i = 0; i < thr->alpha_mods; i++)
      {
         if (thr->overlay && thr->overlay->set_alpha)
            thr->overlay->set_alpha(thr->driver_data, i, thr->alpha_mod[i]);
      }
      thr->alpha_update = false;
   }
   slock_unlock(thr->alpha_lock);
#endif

   if (thr->apply_state_changes)
   {
      if (thr->poke && thr->poke->apply_state_changes)
         thr->poke->apply_state_changes(thr->driver_data);
      thr->apply_state_changes = false;
   }
}