#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_11__ {long long height; int width; } ;
struct TYPE_10__ {int key_frame; int* linesize; int /*<<< orphan*/ ** data; int /*<<< orphan*/  pict_type; } ;
struct TYPE_9__ {long long size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  EINVAL ; 
 long long FFALIGN (int,int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int ff_get_buffer (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int y41p_decode_frame(AVCodecContext *avctx, void *data,
                             int *got_frame, AVPacket *avpkt)
{
    AVFrame *pic = data;
    uint8_t *src = avpkt->data;
    uint8_t *y, *u, *v;
    int i, j, ret;

    if (avpkt->size < 3LL * avctx->height * FFALIGN(avctx->width, 8) / 2) {
        av_log(avctx, AV_LOG_ERROR, "Insufficient input data.\n");
        return AVERROR(EINVAL);
    }

    if ((ret = ff_get_buffer(avctx, pic, 0)) < 0)
        return ret;

    pic->key_frame = 1;
    pic->pict_type = AV_PICTURE_TYPE_I;

    for (i = avctx->height - 1; i >= 0 ; i--) {
        y = &pic->data[0][i * pic->linesize[0]];
        u = &pic->data[1][i * pic->linesize[1]];
        v = &pic->data[2][i * pic->linesize[2]];
        for (j = 0; j < avctx->width; j += 8) {
            *(u++) = *src++;
            *(y++) = *src++;
            *(v++) = *src++;
            *(y++) = *src++;

            *(u++) = *src++;
            *(y++) = *src++;
            *(v++) = *src++;
            *(y++) = *src++;

            *(y++) = *src++;
            *(y++) = *src++;
            *(y++) = *src++;
            *(y++) = *src++;
        }
    }

    *got_frame = 1;

    return avpkt->size;
}