#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nbio_linux_t {int busy; int /*<<< orphan*/  ctx; } ;
struct io_event {int dummy; } ;

/* Variables and functions */
 int io_getevents (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct io_event*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool nbio_linux_iterate(void *data)
{
   struct nbio_linux_t* handle = (struct nbio_linux_t*)data;
   if (!handle)
      return false;
   if (handle->busy)
   {
      struct io_event ev;
      if (io_getevents(handle->ctx, 0, 1, &ev, NULL) == 1)
         handle->busy = false;
   }
   return !handle->busy;
}