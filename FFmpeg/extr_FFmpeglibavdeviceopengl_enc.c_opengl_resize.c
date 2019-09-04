#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* priv_data; } ;
struct TYPE_8__ {int window_width; int window_height; scalar_t__ no_window; scalar_t__ inited; } ;
typedef  TYPE_1__ OpenGLContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DEV_TO_APP_PREPARE_WINDOW_BUFFER ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int avdevice_dev_to_app_control_message (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int opengl_draw (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int opengl_prepare_vertex (TYPE_2__*) ; 

__attribute__((used)) static int opengl_resize(AVFormatContext *h, int width, int height)
{
    int ret = 0;
    OpenGLContext *opengl = h->priv_data;
    opengl->window_width = width;
    opengl->window_height = height;
    if (opengl->inited) {
        if (opengl->no_window &&
            (ret = avdevice_dev_to_app_control_message(h, AV_DEV_TO_APP_PREPARE_WINDOW_BUFFER, NULL , 0)) < 0) {
            av_log(opengl, AV_LOG_ERROR, "Application failed to prepare window buffer.\n");
            goto end;
        }
        if ((ret = opengl_prepare_vertex(h)) < 0)
            goto end;
        ret = opengl_draw(h, NULL, 1, 0);
    }
  end:
    return ret;
}