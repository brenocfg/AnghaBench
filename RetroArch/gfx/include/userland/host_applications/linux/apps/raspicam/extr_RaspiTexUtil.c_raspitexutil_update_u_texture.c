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
struct TYPE_3__ {int /*<<< orphan*/  u_egl_image; int /*<<< orphan*/  u_texture; int /*<<< orphan*/  display; } ;
typedef  TYPE_1__ RASPITEX_STATE ;
typedef  int /*<<< orphan*/  EGLClientBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_IMAGE_BRCM_MULTIMEDIA_U ; 
 int raspitexutil_do_update_texture (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int raspitexutil_update_u_texture(RASPITEX_STATE *raspitex_state,
                                  EGLClientBuffer mm_buf)
{
   return raspitexutil_do_update_texture(raspitex_state->display,
                                         EGL_IMAGE_BRCM_MULTIMEDIA_U, mm_buf,
                                         &raspitex_state->u_texture, &raspitex_state->u_egl_image);
}