#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  uvlinesize; int /*<<< orphan*/  linesize; int /*<<< orphan*/  b8_stride; int /*<<< orphan*/  mb_height; int /*<<< orphan*/  mb_width; int /*<<< orphan*/  mb_stride; int /*<<< orphan*/  out_format; int /*<<< orphan*/  chroma_y_shift; int /*<<< orphan*/  chroma_x_shift; int /*<<< orphan*/  sc; int /*<<< orphan*/  me; int /*<<< orphan*/  avctx; } ;
typedef  int /*<<< orphan*/  Picture ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 int ff_alloc_picture (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alloc_picture(MpegEncContext *s, Picture *pic, int shared)
{
    return ff_alloc_picture(s->avctx, pic, &s->me, &s->sc, shared, 0,
                            s->chroma_x_shift, s->chroma_y_shift, s->out_format,
                            s->mb_stride, s->mb_width, s->mb_height, s->b8_stride,
                            &s->linesize, &s->uvlinesize);
}