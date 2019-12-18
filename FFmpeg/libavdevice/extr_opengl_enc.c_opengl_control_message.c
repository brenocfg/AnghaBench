#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_7__ {TYPE_1__* priv_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  window_height; int /*<<< orphan*/  window_width; } ;
typedef  TYPE_1__ OpenGLContext ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ AVDeviceRect ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_APP_TO_DEV_WINDOW_REPAINT 129 
#define  AV_APP_TO_DEV_WINDOW_SIZE 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOSYS ; 
 int opengl_resize (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int opengl_control_message(AVFormatContext *h, int type, void *data, size_t data_size)
{
    OpenGLContext *opengl = h->priv_data;
    switch(type) {
    case AV_APP_TO_DEV_WINDOW_SIZE:
        if (data) {
            AVDeviceRect *message = data;
            return opengl_resize(h, message->width, message->height);
        }
        return AVERROR(EINVAL);
    case AV_APP_TO_DEV_WINDOW_REPAINT:
        return opengl_resize(h, opengl->window_width, opengl->window_height);
    }
    return AVERROR(ENOSYS);
}