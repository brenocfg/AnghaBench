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
struct TYPE_4__ {TYPE_1__* driver; } ;
typedef  TYPE_2__ thread_video_t ;
struct TYPE_3__ {char const* ident; } ;

/* Variables and functions */
 scalar_t__ video_driver_get_ptr (int) ; 

const char *video_thread_get_ident(void)
{
   const thread_video_t *thr = (const thread_video_t*)
      video_driver_get_ptr(true);

   if (!thr || !thr->driver)
      return NULL;
   return thr->driver->ident;
}