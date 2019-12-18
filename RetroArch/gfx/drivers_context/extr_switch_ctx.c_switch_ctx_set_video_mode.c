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
struct TYPE_3__ {scalar_t__ height; int /*<<< orphan*/  width; } ;
struct TYPE_4__ {int refresh_rate; int /*<<< orphan*/  width; scalar_t__ height; int /*<<< orphan*/  win; int /*<<< orphan*/  egl; TYPE_1__ native_window; } ;
typedef  TYPE_2__ switch_ctx_data_t ;
typedef  int EGLint ;

/* Variables and functions */
#define  EGL_CONTEXT_CLIENT_VERSION 129 
#define  EGL_NONE 128 
 int eglGetError () ; 
 int /*<<< orphan*/  egl_create_context (int /*<<< orphan*/ *,int const*) ; 
 int /*<<< orphan*/  egl_create_surface (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  egl_report_error () ; 
 int /*<<< orphan*/  nwindowSetCrop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  switch_ctx_destroy (void*) ; 
 int /*<<< orphan*/  switch_ctx_get_video_size (void*,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static bool switch_ctx_set_video_mode(void *data,
                                      video_frame_info_t *video_info,
                                      unsigned width, unsigned height,
                                      bool fullscreen)
{
    /* Create an EGL rendering context */
    static const EGLint contextAttributeList[] =
        {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE};

    switch_ctx_data_t *ctx_nx = (switch_ctx_data_t *)data;

    switch_ctx_get_video_size(data, &ctx_nx->width, &ctx_nx->height);

    ctx_nx->native_window.width = ctx_nx->width;
    ctx_nx->native_window.height = ctx_nx->height;

    ctx_nx->refresh_rate = 60;

#ifdef HAVE_EGL
    if (!egl_create_context(&ctx_nx->egl, contextAttributeList))
    {
        egl_report_error();
        goto error;
    }
#endif

#ifdef HAVE_EGL
    if (!egl_create_surface(&ctx_nx->egl, ctx_nx->win))
        goto error;
#endif

    nwindowSetCrop(ctx_nx->win, 0, 1080 - ctx_nx->height, ctx_nx->width, 1080);

    return true;

error:
    printf("[NXGL]: EGL error: %d.\n", eglGetError());
    switch_ctx_destroy(data);

    return false;
}