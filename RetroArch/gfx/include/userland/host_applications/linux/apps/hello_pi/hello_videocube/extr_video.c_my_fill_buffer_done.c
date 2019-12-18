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
typedef  int /*<<< orphan*/  COMPONENT_T ;

/* Variables and functions */
 scalar_t__ OMX_ErrorNone ; 
 scalar_t__ OMX_FillThisBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eglBuffer ; 
 int /*<<< orphan*/  egl_render ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  ilclient_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

void my_fill_buffer_done(void* data, COMPONENT_T* comp)
{
  if (OMX_FillThisBuffer(ilclient_get_handle(egl_render), eglBuffer) != OMX_ErrorNone)
   {
      printf("OMX_FillThisBuffer failed in callback\n");
      exit(1);
   }
}