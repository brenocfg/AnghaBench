#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_info_t ;
typedef  int /*<<< orphan*/  video_driver_t ;
struct TYPE_4__ {int /*<<< orphan*/  video_thread; int /*<<< orphan*/  const* driver; } ;
typedef  TYPE_1__ thread_video_t ;
typedef  int /*<<< orphan*/  input_driver_t ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int video_thread_init (TYPE_1__*,int /*<<< orphan*/  const,int /*<<< orphan*/ **,void**) ; 
 int /*<<< orphan*/  video_thread_set_callbacks (TYPE_1__*,int /*<<< orphan*/  const*) ; 

bool video_init_thread(const video_driver_t **out_driver,
      void **out_data,  input_driver_t **input, void **input_data,
      const video_driver_t *drv, const video_info_t info)
{
   thread_video_t *thr = (thread_video_t*)calloc(1, sizeof(*thr));
   if (!thr)
      return false;

   video_thread_set_callbacks(thr, drv);

   thr->driver = drv;
   *out_driver = &thr->video_thread;
   *out_data   = thr;
   return video_thread_init(thr, info, input, input_data);
}