#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  overlay_interface; int /*<<< orphan*/  set_shader; int /*<<< orphan*/  set_rotation; int /*<<< orphan*/  set_viewport; int /*<<< orphan*/  read_viewport; } ;
typedef  TYPE_1__ video_driver_t ;
struct TYPE_8__ {int /*<<< orphan*/ * poke_interface; int /*<<< orphan*/ * overlay_interface; int /*<<< orphan*/ * set_shader; int /*<<< orphan*/ * set_rotation; int /*<<< orphan*/ * set_viewport; int /*<<< orphan*/ * read_viewport; } ;
struct TYPE_7__ {TYPE_5__ video_thread; } ;
typedef  TYPE_2__ thread_video_t ;

/* Variables and functions */
 TYPE_5__ video_thread ; 

__attribute__((used)) static void video_thread_set_callbacks(
      thread_video_t *thr,
      const video_driver_t *drv)
{
   thr->video_thread = video_thread;

   /* Disable optional features if not present. */
   if (!drv->read_viewport)
      thr->video_thread.read_viewport = NULL;
   if (!drv->set_viewport)
      thr->video_thread.set_viewport = NULL;
   if (!drv->set_rotation)
      thr->video_thread.set_rotation = NULL;
   if (!drv->set_shader)
      thr->video_thread.set_shader = NULL;
#ifdef HAVE_OVERLAY
   if (!drv->overlay_interface)
      thr->video_thread.overlay_interface = NULL;
#endif

   /* Might have to optionally disable poke_interface features as well. */
   if (!thr->video_thread.poke_interface)
      thr->video_thread.poke_interface = NULL;
}