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
struct TYPE_4__ {TYPE_1__* joypad; } ;
typedef  TYPE_2__ linuxraw_input_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* destroy ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  linux_terminal_restore_input () ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void linuxraw_input_free(void *data)
{
   linuxraw_input_t *linuxraw = (linuxraw_input_t*)data;

   if (!linuxraw)
      return;

   if (linuxraw->joypad)
      linuxraw->joypad->destroy();

   linux_terminal_restore_input();
   free(data);
}