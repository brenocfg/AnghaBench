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
struct nbio_linux_t {int busy; int /*<<< orphan*/  cb; int /*<<< orphan*/  ctx; } ;
struct io_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  io_cancel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct io_event*) ; 

__attribute__((used)) static void nbio_linux_cancel(void *data)
{
   struct nbio_linux_t* handle = (struct nbio_linux_t*)data;
   if (!handle)
      return;

   if (handle->busy)
   {
      struct io_event ev;
      io_cancel(handle->ctx, &handle->cb, &ev);
      handle->busy = false;
   }
}