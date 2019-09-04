#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct video_data {int (* open_f ) (char const*,int,int /*<<< orphan*/ ) ;scalar_t__ (* ioctl_f ) (int,int /*<<< orphan*/ ,struct v4l2_capability*) ;int /*<<< orphan*/  (* close_f ) (int) ;int /*<<< orphan*/  munmap_f; int /*<<< orphan*/  mmap_f; int /*<<< orphan*/  read_f; int /*<<< orphan*/  dup_f; scalar_t__ use_libv4l2; } ;
struct v4l2_capability {int capabilities; } ;
struct TYPE_4__ {int flags; struct video_data* priv_data; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVFMT_FLAG_NONBLOCK ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOSYS ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  VIDIOC_QUERYCAP ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct v4l2_capability*) ; 
 int /*<<< orphan*/  mmap ; 
 int /*<<< orphan*/  munmap ; 
 int open (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read ; 
 int stub1 (char const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int,int /*<<< orphan*/ ,struct v4l2_capability*) ; 
 int /*<<< orphan*/  stub3 (int) ; 

__attribute__((used)) static int device_open(AVFormatContext *ctx, const char* device_path)
{
    struct video_data *s = ctx->priv_data;
    struct v4l2_capability cap;
    int fd;
    int err;
    int flags = O_RDWR;

#define SET_WRAPPERS(prefix) do {       \
    s->open_f   = prefix ## open;       \
    s->close_f  = prefix ## close;      \
    s->dup_f    = prefix ## dup;        \
    s->ioctl_f  = prefix ## ioctl;      \
    s->read_f   = prefix ## read;       \
    s->mmap_f   = prefix ## mmap;       \
    s->munmap_f = prefix ## munmap;     \
} while (0)

    if (s->use_libv4l2) {
#if CONFIG_LIBV4L2
        SET_WRAPPERS(v4l2_);
#else
        av_log(ctx, AV_LOG_ERROR, "libavdevice is not built with libv4l2 support.\n");
        return AVERROR(EINVAL);
#endif
    } else {
        SET_WRAPPERS();
    }

#define v4l2_open   s->open_f
#define v4l2_close  s->close_f
#define v4l2_dup    s->dup_f
#define v4l2_ioctl  s->ioctl_f
#define v4l2_read   s->read_f
#define v4l2_mmap   s->mmap_f
#define v4l2_munmap s->munmap_f

    if (ctx->flags & AVFMT_FLAG_NONBLOCK) {
        flags |= O_NONBLOCK;
    }

    fd = v4l2_open(device_path, flags, 0);
    if (fd < 0) {
        err = AVERROR(errno);
        av_log(ctx, AV_LOG_ERROR, "Cannot open video device %s: %s\n",
               device_path, av_err2str(err));
        return err;
    }

    if (v4l2_ioctl(fd, VIDIOC_QUERYCAP, &cap) < 0) {
        err = AVERROR(errno);
        av_log(ctx, AV_LOG_ERROR, "ioctl(VIDIOC_QUERYCAP): %s\n",
               av_err2str(err));
        goto fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "fd:%d capabilities:%x\n",
           fd, cap.capabilities);

    if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
        av_log(ctx, AV_LOG_ERROR, "Not a video capture device.\n");
        err = AVERROR(ENODEV);
        goto fail;
    }

    if (!(cap.capabilities & V4L2_CAP_STREAMING)) {
        av_log(ctx, AV_LOG_ERROR,
               "The device does not support the streaming I/O method.\n");
        err = AVERROR(ENOSYS);
        goto fail;
    }

    return fd;

fail:
    v4l2_close(fd);
    return err;
}