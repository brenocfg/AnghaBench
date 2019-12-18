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

void platform_hint_thread_finished()
{
   /*
      todo: should we do this:

      vcos_thread_deregister_at_exit(client_thread_detach);
      client_thread_detach();

      here?
   */
}