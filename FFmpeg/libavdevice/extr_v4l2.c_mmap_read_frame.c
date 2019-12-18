#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct video_data {int buffers; scalar_t__ frame_size; int /*<<< orphan*/ * buf_start; int /*<<< orphan*/  buffers_queued; int /*<<< orphan*/  fd; } ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct v4l2_buffer {int index; int flags; scalar_t__ bytesused; struct timeval timestamp; int /*<<< orphan*/  memory; int /*<<< orphan*/  type; } ;
struct buff_data {size_t index; struct video_data* s; } ;
struct TYPE_10__ {scalar_t__ video_codec_id; struct video_data* priv_data; } ;
struct TYPE_9__ {scalar_t__ size; scalar_t__ pts; int /*<<< orphan*/  buf; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (scalar_t__) ; 
 scalar_t__ AV_CODEC_ID_CPIA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOMEM ; 
 int FFMAX (int,int) ; 
 int INT64_C (int) ; 
 int V4L2_BUF_FLAG_ERROR ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/  VIDIOC_DQBUF ; 
 int /*<<< orphan*/  atomic_fetch_add (int /*<<< orphan*/ *,int) ; 
 int atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_buffer_create (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct buff_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 int /*<<< orphan*/  av_freep (struct buff_data**) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 struct buff_data* av_malloc (int) ; 
 int av_new_packet (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_1__*) ; 
 int /*<<< orphan*/  convert_timestamp (TYPE_2__*,scalar_t__*) ; 
 int enqueue_buffer (struct video_data*,struct v4l2_buffer*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmap_release_buffer ; 
 int v4l2_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_buffer*) ; 

__attribute__((used)) static int mmap_read_frame(AVFormatContext *ctx, AVPacket *pkt)
{
    struct video_data *s = ctx->priv_data;
    struct v4l2_buffer buf = {
        .type   = V4L2_BUF_TYPE_VIDEO_CAPTURE,
        .memory = V4L2_MEMORY_MMAP
    };
    struct timeval buf_ts;
    int res;

    pkt->size = 0;

    /* FIXME: Some special treatment might be needed in case of loss of signal... */
    while ((res = v4l2_ioctl(s->fd, VIDIOC_DQBUF, &buf)) < 0 && (errno == EINTR));
    if (res < 0) {
        if (errno == EAGAIN)
            return AVERROR(EAGAIN);

        res = AVERROR(errno);
        av_log(ctx, AV_LOG_ERROR, "ioctl(VIDIOC_DQBUF): %s\n",
               av_err2str(res));
        return res;
    }

    buf_ts = buf.timestamp;

    if (buf.index >= s->buffers) {
        av_log(ctx, AV_LOG_ERROR, "Invalid buffer index received.\n");
        return AVERROR(EINVAL);
    }
    atomic_fetch_add(&s->buffers_queued, -1);
    // always keep at least one buffer queued
    av_assert0(atomic_load(&s->buffers_queued) >= 1);

#ifdef V4L2_BUF_FLAG_ERROR
    if (buf.flags & V4L2_BUF_FLAG_ERROR) {
        av_log(ctx, AV_LOG_WARNING,
               "Dequeued v4l2 buffer contains corrupted data (%d bytes).\n",
               buf.bytesused);
        buf.bytesused = 0;
    } else
#endif
    {
        /* CPIA is a compressed format and we don't know the exact number of bytes
         * used by a frame, so set it here as the driver announces it. */
        if (ctx->video_codec_id == AV_CODEC_ID_CPIA)
            s->frame_size = buf.bytesused;

        if (s->frame_size > 0 && buf.bytesused != s->frame_size) {
            av_log(ctx, AV_LOG_WARNING,
                   "Dequeued v4l2 buffer contains %d bytes, but %d were expected. Flags: 0x%08X.\n",
                   buf.bytesused, s->frame_size, buf.flags);
            buf.bytesused = 0;
        }
    }

    /* Image is at s->buff_start[buf.index] */
    if (atomic_load(&s->buffers_queued) == FFMAX(s->buffers / 8, 1)) {
        /* when we start getting low on queued buffers, fall back on copying data */
        res = av_new_packet(pkt, buf.bytesused);
        if (res < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error allocating a packet.\n");
            enqueue_buffer(s, &buf);
            return res;
        }
        memcpy(pkt->data, s->buf_start[buf.index], buf.bytesused);

        res = enqueue_buffer(s, &buf);
        if (res) {
            av_packet_unref(pkt);
            return res;
        }
    } else {
        struct buff_data *buf_descriptor;

        pkt->data     = s->buf_start[buf.index];
        pkt->size     = buf.bytesused;

        buf_descriptor = av_malloc(sizeof(struct buff_data));
        if (!buf_descriptor) {
            /* Something went wrong... Since av_malloc() failed, we cannot even
             * allocate a buffer for memcpying into it
             */
            av_log(ctx, AV_LOG_ERROR, "Failed to allocate a buffer descriptor\n");
            enqueue_buffer(s, &buf);

            return AVERROR(ENOMEM);
        }
        buf_descriptor->index = buf.index;
        buf_descriptor->s     = s;

        pkt->buf = av_buffer_create(pkt->data, pkt->size, mmap_release_buffer,
                                    buf_descriptor, 0);
        if (!pkt->buf) {
            av_log(ctx, AV_LOG_ERROR, "Failed to create a buffer\n");
            enqueue_buffer(s, &buf);
            av_freep(&buf_descriptor);
            return AVERROR(ENOMEM);
        }
    }
    pkt->pts = buf_ts.tv_sec * INT64_C(1000000) + buf_ts.tv_usec;
    convert_timestamp(ctx, &pkt->pts);

    return pkt->size;
}