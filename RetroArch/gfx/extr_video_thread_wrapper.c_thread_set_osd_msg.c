#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_4__ {int /*<<< orphan*/  driver_data; TYPE_1__* poke; } ;
typedef  TYPE_2__ thread_video_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_osd_msg ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,void const*,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,void const*,void*) ; 

__attribute__((used)) static void thread_set_osd_msg(void *data,
      video_frame_info_t *video_info,
      const char *msg,
      const void *params, void *font)
{
   thread_video_t *thr = (thread_video_t*)data;

   if (!thr)
      return;

   /* TODO : find a way to determine if the calling
    * thread is the driver thread or not. */
   if (thr->poke && thr->poke->set_osd_msg)
      thr->poke->set_osd_msg(thr->driver_data, video_info, msg, params, font);
}