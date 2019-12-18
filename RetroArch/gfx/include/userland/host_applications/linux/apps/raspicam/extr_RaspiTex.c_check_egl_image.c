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
struct TYPE_3__ {scalar_t__ egl_image; scalar_t__ y_egl_image; scalar_t__ u_egl_image; scalar_t__ v_egl_image; } ;
typedef  TYPE_1__ RASPITEX_STATE ;

/* Variables and functions */
 scalar_t__ EGL_NO_IMAGE_KHR ; 

__attribute__((used)) static int check_egl_image(RASPITEX_STATE *state)
{
   if (state->egl_image == EGL_NO_IMAGE_KHR &&
         state->y_egl_image == EGL_NO_IMAGE_KHR &&
         state->u_egl_image == EGL_NO_IMAGE_KHR &&
         state->v_egl_image == EGL_NO_IMAGE_KHR)
      return -1;
   else
      return 0;
}