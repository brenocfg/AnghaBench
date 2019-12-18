#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_18__ {int num_planes; TYPE_5__* context; TYPE_1__* plane_info; } ;
typedef  TYPE_6__ V4L2Buffer ;
struct TYPE_19__ {int format; int* linesize; int* data; TYPE_11__** buf; } ;
struct TYPE_14__ {int height; } ;
struct TYPE_15__ {TYPE_2__ pix_mp; } ;
struct TYPE_16__ {TYPE_3__ fmt; } ;
struct TYPE_17__ {int av_pix_fmt; TYPE_4__ format; } ;
struct TYPE_13__ {int bytesperline; } ;
struct TYPE_12__ {int data; } ;
typedef  TYPE_7__ AVFrame ;

/* Variables and functions */
#define  AV_PIX_FMT_NV12 130 
#define  AV_PIX_FMT_NV21 129 
#define  AV_PIX_FMT_YUV420P 128 
 int v4l2_buf_to_bufref (TYPE_6__*,int,TYPE_11__**) ; 

__attribute__((used)) static int v4l2_buffer_buf_to_swframe(AVFrame *frame, V4L2Buffer *avbuf)
{
    int i, ret;

    frame->format = avbuf->context->av_pix_fmt;

    for (i = 0; i < avbuf->num_planes; i++) {
        ret = v4l2_buf_to_bufref(avbuf, i, &frame->buf[i]);
        if (ret)
            return ret;

        frame->linesize[i] = avbuf->plane_info[i].bytesperline;
        frame->data[i] = frame->buf[i]->data;
    }

    /* fixup special cases */
    switch (avbuf->context->av_pix_fmt) {
    case AV_PIX_FMT_NV12:
    case AV_PIX_FMT_NV21:
        if (avbuf->num_planes > 1)
            break;
        frame->linesize[1] = avbuf->plane_info[0].bytesperline;
        frame->data[1] = frame->buf[0]->data + avbuf->plane_info[0].bytesperline * avbuf->context->format.fmt.pix_mp.height;
        break;

    case AV_PIX_FMT_YUV420P:
        if (avbuf->num_planes > 1)
            break;
        frame->linesize[1] = avbuf->plane_info[0].bytesperline >> 1;
        frame->linesize[2] = avbuf->plane_info[0].bytesperline >> 1;
        frame->data[1] = frame->buf[0]->data + avbuf->plane_info[0].bytesperline * avbuf->context->format.fmt.pix_mp.height;
        frame->data[2] = frame->data[1] + ((avbuf->plane_info[0].bytesperline * avbuf->context->format.fmt.pix_mp.height) >> 2);
        break;

    default:
        break;
    }

    return 0;
}