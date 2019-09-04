#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int size; int data; } ;
struct TYPE_13__ {int height; } ;
struct TYPE_12__ {int mb_stride; } ;
struct TYPE_11__ {int /*<<< orphan*/  qscale_table_buf; } ;
typedef  TYPE_1__ Picture ;
typedef  TYPE_2__ MpegEncContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVBufferRef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 TYPE_4__* av_buffer_ref (int /*<<< orphan*/ ) ; 
 int av_frame_set_qp_table (TYPE_3__*,TYPE_4__*,int,int) ; 

int ff_mpv_export_qp_table(MpegEncContext *s, AVFrame *f, Picture *p, int qp_type)
{
    AVBufferRef *ref = av_buffer_ref(p->qscale_table_buf);
    int offset = 2*s->mb_stride + 1;
    if(!ref)
        return AVERROR(ENOMEM);
    av_assert0(ref->size >= offset + s->mb_stride * ((f->height+15)/16));
    ref->size -= offset;
    ref->data += offset;
    return av_frame_set_qp_table(f, ref, s->mb_stride, qp_type);
}