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
struct TYPE_7__ {TYPE_2__* priv_data; } ;
struct TYPE_5__ {int state; scalar_t__ last_index; scalar_t__ index; scalar_t__ overread_index; scalar_t__ overread; scalar_t__ frame_start_found; } ;
struct TYPE_6__ {scalar_t__ pp_time; scalar_t__ bitstream_buffer_size; TYPE_1__ parse_context; scalar_t__ closed_gop; scalar_t__ mb_y; scalar_t__ mb_x; int /*<<< orphan*/  next_picture; int /*<<< orphan*/  avctx; int /*<<< orphan*/  last_picture; int /*<<< orphan*/  current_picture; int /*<<< orphan*/ * next_picture_ptr; int /*<<< orphan*/  last_picture_ptr; int /*<<< orphan*/  current_picture_ptr; int /*<<< orphan*/ * picture; } ;
typedef  TYPE_2__ MpegEncContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int MAX_PICTURE_COUNT ; 
 int /*<<< orphan*/  ff_mpeg_unref_picture (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ff_mpeg_flush(AVCodecContext *avctx){
    int i;
    MpegEncContext *s = avctx->priv_data;

    if (!s || !s->picture)
        return;

    for (i = 0; i < MAX_PICTURE_COUNT; i++)
        ff_mpeg_unref_picture(s->avctx, &s->picture[i]);
    s->current_picture_ptr = s->last_picture_ptr = s->next_picture_ptr = NULL;

    ff_mpeg_unref_picture(s->avctx, &s->current_picture);
    ff_mpeg_unref_picture(s->avctx, &s->last_picture);
    ff_mpeg_unref_picture(s->avctx, &s->next_picture);

    s->mb_x= s->mb_y= 0;
    s->closed_gop= 0;

    s->parse_context.state= -1;
    s->parse_context.frame_start_found= 0;
    s->parse_context.overread= 0;
    s->parse_context.overread_index= 0;
    s->parse_context.index= 0;
    s->parse_context.last_index= 0;
    s->bitstream_buffer_size=0;
    s->pp_time=0;
}