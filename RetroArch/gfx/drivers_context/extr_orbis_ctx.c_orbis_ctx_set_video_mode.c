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
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_3__ {int refresh_rate; TYPE_2__ native_window; int /*<<< orphan*/  egl; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ orbis_ctx_data_t ;
typedef  int EGLint ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_ORBISGL_HEIGHT ; 
 int /*<<< orphan*/  ATTR_ORBISGL_WIDTH ; 
#define  EGL_CONTEXT_CLIENT_VERSION 129 
#define  EGL_NONE 128 
 int eglGetError () ; 
 int /*<<< orphan*/  egl_create_context (int /*<<< orphan*/ *,int const*) ; 
 int /*<<< orphan*/  egl_create_surface (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  egl_report_error () ; 
 int /*<<< orphan*/  orbis_ctx_destroy (void*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static bool orbis_ctx_set_video_mode(void *data,
                                      video_frame_info_t *video_info,
                                      unsigned width, unsigned height,
                                      bool fullscreen)
{
    /* Create an EGL rendering context */
    static const EGLint contextAttributeList[] =
        {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE};

    orbis_ctx_data_t *ctx_orbis = (orbis_ctx_data_t *)data;

    ctx_orbis->width = ATTR_ORBISGL_WIDTH;
    ctx_orbis->height = ATTR_ORBISGL_HEIGHT;

    ctx_orbis->native_window.width = ctx_orbis->width;
    ctx_orbis->native_window.height = ctx_orbis->height;

    ctx_orbis->refresh_rate = 60;

#ifdef HAVE_EGL
    if (!egl_create_context(&ctx_orbis->egl, contextAttributeList))
    {
        egl_report_error();
        goto error;
    }
#endif

#ifdef HAVE_EGL
    if (!egl_create_surface(&ctx_orbis->egl, &ctx_orbis->native_window))
        goto error;
#endif

    return true;

error:
    printf("[ctx_orbis]: EGL error: %d.\n", eglGetError());
    orbis_ctx_destroy(data);

    return false;
}