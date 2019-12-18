#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_16__ {TYPE_4__* sps; } ;
struct TYPE_18__ {scalar_t__ threads_type; int /*<<< orphan*/  seq_decode; TYPE_5__ ps; TYPE_1__* avctx; } ;
struct TYPE_17__ {int poc; int /*<<< orphan*/  tf; scalar_t__ flags; int /*<<< orphan*/  sequence; TYPE_3__* frame; } ;
struct TYPE_15__ {int bit_depth; int height; int* vshift; int width; int* hshift; int /*<<< orphan*/  pixel_shift; } ;
struct TYPE_14__ {int* linesize; int /*<<< orphan*/ ** data; TYPE_2__** buf; } ;
struct TYPE_13__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_12__ {int /*<<< orphan*/  hwaccel; } ;
typedef  TYPE_6__ HEVCFrame ;
typedef  TYPE_7__ HEVCContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WN16 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ FF_THREAD_FRAME ; 
 int /*<<< orphan*/  INT_MAX ; 
 TYPE_6__* alloc_frame (TYPE_7__*) ; 
 int /*<<< orphan*/  av_memcpy_backptr (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ff_thread_report_progress (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HEVCFrame *generate_missing_ref(HEVCContext *s, int poc)
{
    HEVCFrame *frame;
    int i, y;

    frame = alloc_frame(s);
    if (!frame)
        return NULL;

    if (!s->avctx->hwaccel) {
        if (!s->ps.sps->pixel_shift) {
            for (i = 0; frame->frame->buf[i]; i++)
                memset(frame->frame->buf[i]->data, 1 << (s->ps.sps->bit_depth - 1),
                       frame->frame->buf[i]->size);
        } else {
            for (i = 0; frame->frame->data[i]; i++)
                for (y = 0; y < (s->ps.sps->height >> s->ps.sps->vshift[i]); y++) {
                    uint8_t *dst = frame->frame->data[i] + y * frame->frame->linesize[i];
                    AV_WN16(dst, 1 << (s->ps.sps->bit_depth - 1));
                    av_memcpy_backptr(dst + 2, 2, 2*(s->ps.sps->width >> s->ps.sps->hshift[i]) - 2);
                }
        }
    }

    frame->poc      = poc;
    frame->sequence = s->seq_decode;
    frame->flags    = 0;

    if (s->threads_type == FF_THREAD_FRAME)
        ff_thread_report_progress(&frame->tf, INT_MAX, 0);

    return frame;
}