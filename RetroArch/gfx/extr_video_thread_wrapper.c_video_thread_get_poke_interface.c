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
typedef  int /*<<< orphan*/  video_poke_interface_t ;
struct TYPE_4__ {int /*<<< orphan*/  poke; int /*<<< orphan*/  driver_data; TYPE_1__* driver; } ;
typedef  TYPE_2__ thread_video_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* poke_interface ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_poke ; 

__attribute__((used)) static void video_thread_get_poke_interface(
      void *data,
      const video_poke_interface_t **iface)
{
   thread_video_t *thr = (thread_video_t*)data;

   if (thr->driver->poke_interface)
   {
      *iface = &thread_poke;
      thr->driver->poke_interface(thr->driver_data, &thr->poke);
   }
   else
      *iface = NULL;
}