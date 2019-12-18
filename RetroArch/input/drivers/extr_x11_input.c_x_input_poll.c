#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* joypad; int /*<<< orphan*/  state; int /*<<< orphan*/  display; } ;
typedef  TYPE_2__ x11_input_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* poll ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  XQueryKeymap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 () ; 
 scalar_t__ video_driver_has_focus () ; 
 int /*<<< orphan*/  x_input_poll_mouse (TYPE_2__*) ; 

__attribute__((used)) static void x_input_poll(void *data)
{
   x11_input_t *x11 = (x11_input_t*)data;

   if (video_driver_has_focus())
      XQueryKeymap(x11->display, x11->state);
   else
      memset(x11->state, 0, sizeof(x11->state));

   x_input_poll_mouse(x11);

   if (x11->joypad)
      x11->joypad->poll();
}