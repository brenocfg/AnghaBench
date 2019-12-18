#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_driver_t ;
struct TYPE_2__ {void* driver_data; int /*<<< orphan*/ * driver; } ;
typedef  TYPE_1__ thread_video_t ;

/* Variables and functions */
 scalar_t__ video_driver_get_ptr (int) ; 

void *video_thread_get_ptr(const video_driver_t **drv)
{
   const thread_video_t *thr = (const thread_video_t*)
      video_driver_get_ptr(true);

   if (drv)
      *drv = thr->driver;

   if (!thr)
      return NULL;
   return thr->driver_data;
}