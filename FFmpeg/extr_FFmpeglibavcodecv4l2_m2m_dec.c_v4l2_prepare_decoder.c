#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sub ;
struct v4l2_event_subscription {int /*<<< orphan*/  type; } ;
struct TYPE_5__ {scalar_t__ height; scalar_t__ width; } ;
struct TYPE_4__ {int /*<<< orphan*/  avctx; int /*<<< orphan*/  fd; TYPE_2__ output; } ;
typedef  TYPE_1__ V4L2m2mContext ;
typedef  TYPE_2__ V4L2Context ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  V4L2_EVENT_SOURCE_CHANGE ; 
 int /*<<< orphan*/  VIDIOC_SUBSCRIBE_EVENT ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_event_subscription*) ; 
 int /*<<< orphan*/  memset (struct v4l2_event_subscription*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int v4l2_prepare_decoder(V4L2m2mContext *s)
{
    struct v4l2_event_subscription sub;
    V4L2Context *output = &s->output;
    int ret;

    /**
     * requirements
     */
    memset(&sub, 0, sizeof(sub));
    sub.type = V4L2_EVENT_SOURCE_CHANGE;
    ret = ioctl(s->fd, VIDIOC_SUBSCRIBE_EVENT, &sub);
    if ( ret < 0) {
        if (output->height == 0 || output->width == 0) {
            av_log(s->avctx, AV_LOG_ERROR,
                "the v4l2 driver does not support VIDIOC_SUBSCRIBE_EVENT\n"
                "you must provide codec_height and codec_width on input\n");
            return ret;
        }
    }

    return 0;
}