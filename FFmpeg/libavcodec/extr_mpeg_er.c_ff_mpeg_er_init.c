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
struct TYPE_5__ {int mb_height; int mb_stride; int /*<<< orphan*/  error_status_table; int /*<<< orphan*/  er_temp_buffer; TYPE_1__* opaque; int /*<<< orphan*/  decode_mb; int /*<<< orphan*/ * dc_val; int /*<<< orphan*/  mbintra_table; int /*<<< orphan*/  mbskip_table; int /*<<< orphan*/  b8_stride; int /*<<< orphan*/  mb_width; int /*<<< orphan*/  mb_num; int /*<<< orphan*/  mb_index2xy; int /*<<< orphan*/  avctx; } ;
struct TYPE_4__ {int mb_height; int mb_stride; int /*<<< orphan*/ * dc_val; int /*<<< orphan*/  mbintra_table; int /*<<< orphan*/  mbskip_table; int /*<<< orphan*/  b8_stride; int /*<<< orphan*/  mb_width; int /*<<< orphan*/  mb_num; int /*<<< orphan*/  mb_index2xy; int /*<<< orphan*/  avctx; TYPE_2__ er; } ;
typedef  TYPE_1__ MpegEncContext ;
typedef  TYPE_2__ ERContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_malloc (int) ; 
 int /*<<< orphan*/  av_mallocz (int) ; 
 int /*<<< orphan*/  mpeg_er_decode_mb ; 

int ff_mpeg_er_init(MpegEncContext *s)
{
    ERContext *er = &s->er;
    int mb_array_size = s->mb_height * s->mb_stride;
    int i;

    er->avctx       = s->avctx;

    er->mb_index2xy = s->mb_index2xy;
    er->mb_num      = s->mb_num;
    er->mb_width    = s->mb_width;
    er->mb_height   = s->mb_height;
    er->mb_stride   = s->mb_stride;
    er->b8_stride   = s->b8_stride;

    er->er_temp_buffer     = av_malloc(s->mb_height * s->mb_stride * (4*sizeof(int) + 1));
    er->error_status_table = av_mallocz(mb_array_size);
    if (!er->er_temp_buffer || !er->error_status_table)
        goto fail;

    er->mbskip_table  = s->mbskip_table;
    er->mbintra_table = s->mbintra_table;

    for (i = 0; i < FF_ARRAY_ELEMS(s->dc_val); i++)
        er->dc_val[i] = s->dc_val[i];

    er->decode_mb = mpeg_er_decode_mb;
    er->opaque    = s;

    return 0;
fail:
    av_freep(&er->er_temp_buffer);
    av_freep(&er->error_status_table);
    return AVERROR(ENOMEM);
}