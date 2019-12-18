#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  windows; } ;
typedef  scalar_t__ EGLNativeWindowType ;
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;
typedef  TYPE_1__ CLIENT_PROCESS_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  khrn_pointer_map_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

EGLNativeWindowType client_egl_get_window(CLIENT_THREAD_STATE_T *thread, CLIENT_PROCESS_STATE_T *process, EGLNativeWindowType window)
{
   EGLNativeWindowType win = (EGLNativeWindowType)khrn_pointer_map_lookup(&process->windows, (uint32_t)(size_t)window);

   return win;
}