#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* priv_data; } ;
struct TYPE_7__ {scalar_t__ context_initialized; scalar_t__ mb_y; int /*<<< orphan*/  cur_pic; int /*<<< orphan*/ * cur_pic_ptr; int /*<<< orphan*/ * DPB; int /*<<< orphan*/  sei; int /*<<< orphan*/  delayed_pic; } ;
typedef  TYPE_1__ H264Context ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int H264_MAX_PICTURE_COUNT ; 
 int /*<<< orphan*/  ff_h264_flush_change (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_h264_free_tables (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_h264_sei_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_h264_unref_picture (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void flush_dpb(AVCodecContext *avctx)
{
    H264Context *h = avctx->priv_data;
    int i;

    memset(h->delayed_pic, 0, sizeof(h->delayed_pic));

    ff_h264_flush_change(h);
    ff_h264_sei_uninit(&h->sei);

    for (i = 0; i < H264_MAX_PICTURE_COUNT; i++)
        ff_h264_unref_picture(h, &h->DPB[i]);
    h->cur_pic_ptr = NULL;
    ff_h264_unref_picture(h, &h->cur_pic);

    h->mb_y = 0;

    ff_h264_free_tables(h);
    h->context_initialized = 0;
}