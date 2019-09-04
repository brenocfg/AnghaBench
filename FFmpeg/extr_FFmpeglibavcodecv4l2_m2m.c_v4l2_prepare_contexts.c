#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_capability {int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
typedef  int /*<<< orphan*/  cap ;
struct TYPE_6__ {char* name; int /*<<< orphan*/  type; scalar_t__ done; } ;
struct TYPE_5__ {char* name; int /*<<< orphan*/  type; scalar_t__ done; } ;
struct TYPE_7__ {TYPE_2__ output; TYPE_1__ capture; int /*<<< orphan*/  avctx; int /*<<< orphan*/  fd; int /*<<< orphan*/  refsync; int /*<<< orphan*/  refcount; } ;
typedef  TYPE_3__ V4L2m2mContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 int /*<<< orphan*/  VIDIOC_QUERYCAP ; 
 int /*<<< orphan*/  atomic_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_capability*) ; 
 int /*<<< orphan*/  memset (struct v4l2_capability*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ v4l2_mplane_video (struct v4l2_capability*) ; 
 scalar_t__ v4l2_splane_video (struct v4l2_capability*) ; 

__attribute__((used)) static int v4l2_prepare_contexts(V4L2m2mContext* s)
{
    struct v4l2_capability cap;
    int ret;

    s->capture.done = s->output.done = 0;
    s->capture.name = "capture";
    s->output.name = "output ";
    atomic_init(&s->refcount, 0);
    sem_init(&s->refsync, 0, 0);

    memset(&cap, 0, sizeof(cap));
    ret = ioctl(s->fd, VIDIOC_QUERYCAP, &cap);
    if (ret < 0)
        return ret;

    av_log(s->avctx, AV_LOG_INFO, "driver '%s' on card '%s'\n", cap.driver, cap.card);

    if (v4l2_mplane_video(&cap)) {
        s->capture.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
        s->output.type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
        return 0;
    }

    if (v4l2_splane_video(&cap)) {
        s->capture.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        s->output.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
        return 0;
    }

    return AVERROR(EINVAL);
}