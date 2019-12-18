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

/* Variables and functions */
 int /*<<< orphan*/  CFRunLoopSourceSignal (scalar_t__) ; 
 scalar_t__ btstack_quit_source ; 
 int /*<<< orphan*/ * btstack_thread ; 
 int /*<<< orphan*/  btstack_thread_func ; 
 int /*<<< orphan*/  btstack_try_load () ; 
 int /*<<< orphan*/ * sthread_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sthread_join (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btstack_set_poweron(bool on)
{
   if (!btstack_try_load())
      return;

   if (on && !btstack_thread)
      btstack_thread = sthread_create(btstack_thread_func, NULL);
   else if (!on && btstack_thread && btstack_quit_source)
   {
#ifdef __APPLE__
      CFRunLoopSourceSignal(btstack_quit_source);
#endif
      sthread_join(btstack_thread);
      btstack_thread = NULL;
   }
}