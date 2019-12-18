#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  inited; } ;
struct TYPE_6__ {int /*<<< orphan*/  error; } ;
typedef  scalar_t__ EGLDisplay ;
typedef  scalar_t__ EGLBoolean ;
typedef  TYPE_1__ CLIENT_THREAD_STATE_T ;
typedef  TYPE_2__ CLIENT_PROCESS_STATE_T ;

/* Variables and functions */
 TYPE_2__* CLIENT_GET_PROCESS_STATE () ; 
 int /*<<< orphan*/  EGL_BAD_DISPLAY ; 
 int /*<<< orphan*/  EGL_NOT_INITIALIZED ; 

CLIENT_PROCESS_STATE_T *client_egl_get_process_state(CLIENT_THREAD_STATE_T *thread, EGLDisplay dpy, EGLBoolean check_inited)
{
   if ((size_t)dpy == 1) {
      CLIENT_PROCESS_STATE_T *process = CLIENT_GET_PROCESS_STATE();

      if (check_inited && !process->inited) {
         thread->error = EGL_NOT_INITIALIZED;
         return NULL;
      } else
         return process;
   } else {
      thread->error = EGL_BAD_DISPLAY;
      return NULL;
   }
}