#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_6__ {int bits; int mb_height; int mb_width; int* nb_blocks; int* comp_index; int* h_scount; int* v_scount; int* linesize; int width; int height; int /*<<< orphan*/  gb; scalar_t__ restart_count; scalar_t__ restart_interval; TYPE_1__* picture_ptr; int /*<<< orphan*/ * dc_index; scalar_t__ bottom_field; scalar_t__ interlaced; int /*<<< orphan*/  avctx; } ;
struct TYPE_5__ {int** data; } ;
typedef  TYPE_2__ MJpegDecodeContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  PREDICT (int,int,int,int,int) ; 
 int /*<<< orphan*/  align_get_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int mjpeg_decode_dc (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ljpeg_decode_yuv_scan(MJpegDecodeContext *s, int predictor,
                                 int point_transform, int nb_components)
{
    int i, mb_x, mb_y, mask;
    int bits= (s->bits+7)&~7;
    int resync_mb_y = 0;
    int resync_mb_x = 0;

    point_transform += bits - s->bits;
    mask = ((1 << s->bits) - 1) << point_transform;

    av_assert0(nb_components>=1 && nb_components<=4);

    for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
        for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
            if (get_bits_left(&s->gb) < 1) {
                av_log(s->avctx, AV_LOG_ERROR, "bitstream end in yuv_scan\n");
                return AVERROR_INVALIDDATA;
            }
            if (s->restart_interval && !s->restart_count){
                s->restart_count = s->restart_interval;
                resync_mb_x = mb_x;
                resync_mb_y = mb_y;
            }

            if(!mb_x || mb_y == resync_mb_y || mb_y == resync_mb_y+1 && mb_x < resync_mb_x || s->interlaced){
                int toprow  = mb_y == resync_mb_y || mb_y == resync_mb_y+1 && mb_x < resync_mb_x;
                int leftcol = !mb_x || mb_y == resync_mb_y && mb_x == resync_mb_x;
                for (i = 0; i < nb_components; i++) {
                    uint8_t *ptr;
                    uint16_t *ptr16;
                    int n, h, v, x, y, c, j, linesize;
                    n = s->nb_blocks[i];
                    c = s->comp_index[i];
                    h = s->h_scount[i];
                    v = s->v_scount[i];
                    x = 0;
                    y = 0;
                    linesize= s->linesize[c];

                    if(bits>8) linesize /= 2;

                    for(j=0; j<n; j++) {
                        int pred, dc;

                        dc = mjpeg_decode_dc(s, s->dc_index[i]);
                        if(dc == 0xFFFFF)
                            return -1;
                        if (   h * mb_x + x >= s->width
                            || v * mb_y + y >= s->height) {
                            // Nothing to do
                        } else if (bits<=8) {
                            ptr = s->picture_ptr->data[c] + (linesize * (v * mb_y + y)) + (h * mb_x + x); //FIXME optimize this crap
                            if(y==0 && toprow){
                                if(x==0 && leftcol){
                                    pred= 1 << (bits - 1);
                                }else{
                                    pred= ptr[-1];
                                }
                            }else{
                                if(x==0 && leftcol){
                                    pred= ptr[-linesize];
                                }else{
                                    PREDICT(pred, ptr[-linesize-1], ptr[-linesize], ptr[-1], predictor);
                                }
                            }

                            if (s->interlaced && s->bottom_field)
                                ptr += linesize >> 1;
                            pred &= mask;
                            *ptr= pred + ((unsigned)dc << point_transform);
                        }else{
                            ptr16 = (uint16_t*)(s->picture_ptr->data[c] + 2*(linesize * (v * mb_y + y)) + 2*(h * mb_x + x)); //FIXME optimize this crap
                            if(y==0 && toprow){
                                if(x==0 && leftcol){
                                    pred= 1 << (bits - 1);
                                }else{
                                    pred= ptr16[-1];
                                }
                            }else{
                                if(x==0 && leftcol){
                                    pred= ptr16[-linesize];
                                }else{
                                    PREDICT(pred, ptr16[-linesize-1], ptr16[-linesize], ptr16[-1], predictor);
                                }
                            }

                            if (s->interlaced && s->bottom_field)
                                ptr16 += linesize >> 1;
                            pred &= mask;
                            *ptr16= pred + ((unsigned)dc << point_transform);
                        }
                        if (++x == h) {
                            x = 0;
                            y++;
                        }
                    }
                }
            } else {
                for (i = 0; i < nb_components; i++) {
                    uint8_t *ptr;
                    uint16_t *ptr16;
                    int n, h, v, x, y, c, j, linesize, dc;
                    n        = s->nb_blocks[i];
                    c        = s->comp_index[i];
                    h        = s->h_scount[i];
                    v        = s->v_scount[i];
                    x        = 0;
                    y        = 0;
                    linesize = s->linesize[c];

                    if(bits>8) linesize /= 2;

                    for (j = 0; j < n; j++) {
                        int pred;

                        dc = mjpeg_decode_dc(s, s->dc_index[i]);
                        if(dc == 0xFFFFF)
                            return -1;
                        if (   h * mb_x + x >= s->width
                            || v * mb_y + y >= s->height) {
                            // Nothing to do
                        } else if (bits<=8) {
                            ptr = s->picture_ptr->data[c] +
                              (linesize * (v * mb_y + y)) +
                              (h * mb_x + x); //FIXME optimize this crap
                            PREDICT(pred, ptr[-linesize-1], ptr[-linesize], ptr[-1], predictor);

                            pred &= mask;
                            *ptr = pred + ((unsigned)dc << point_transform);
                        }else{
                            ptr16 = (uint16_t*)(s->picture_ptr->data[c] + 2*(linesize * (v * mb_y + y)) + 2*(h * mb_x + x)); //FIXME optimize this crap
                            PREDICT(pred, ptr16[-linesize-1], ptr16[-linesize], ptr16[-1], predictor);

                            pred &= mask;
                            *ptr16= pred + ((unsigned)dc << point_transform);
                        }

                        if (++x == h) {
                            x = 0;
                            y++;
                        }
                    }
                }
            }
            if (s->restart_interval && !--s->restart_count) {
                align_get_bits(&s->gb);
                skip_bits(&s->gb, 16); /* skip RSTn */
            }
        }
    }
    return 0;
}