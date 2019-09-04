#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_11__ {int height; int width; TYPE_4__* priv_data; } ;
struct TYPE_7__ {int (* pix_sum ) (int*,int) ;int (* pix_norm1 ) (int*,int) ;} ;
struct TYPE_8__ {int mb_height; int linesize; int mb_width; TYPE_1__ mpvencdsp; } ;
struct TYPE_10__ {int interlaced; int bit_depth; int** src; TYPE_3__* mb_cmp; TYPE_2__ m; struct TYPE_10__** thread; } ;
struct TYPE_9__ {int value; unsigned int mb; } ;
typedef  TYPE_4__ DNXHDEncContext ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int stub1 (int*,int) ; 
 int stub2 (int*,int) ; 

__attribute__((used)) static int dnxhd_mb_var_thread(AVCodecContext *avctx, void *arg,
                               int jobnr, int threadnr)
{
    DNXHDEncContext *ctx = avctx->priv_data;
    int mb_y = jobnr, mb_x, x, y;
    int partial_last_row = (mb_y == ctx->m.mb_height - 1) &&
                           ((avctx->height >> ctx->interlaced) & 0xF);

    ctx = ctx->thread[threadnr];
    if (ctx->bit_depth == 8) {
        uint8_t *pix = ctx->thread[0]->src[0] + ((mb_y << 4) * ctx->m.linesize);
        for (mb_x = 0; mb_x < ctx->m.mb_width; ++mb_x, pix += 16) {
            unsigned mb = mb_y * ctx->m.mb_width + mb_x;
            int sum;
            int varc;

            if (!partial_last_row && mb_x * 16 <= avctx->width - 16 && (avctx->width % 16) == 0) {
                sum  = ctx->m.mpvencdsp.pix_sum(pix, ctx->m.linesize);
                varc = ctx->m.mpvencdsp.pix_norm1(pix, ctx->m.linesize);
            } else {
                int bw = FFMIN(avctx->width - 16 * mb_x, 16);
                int bh = FFMIN((avctx->height >> ctx->interlaced) - 16 * mb_y, 16);
                sum = varc = 0;
                for (y = 0; y < bh; y++) {
                    for (x = 0; x < bw; x++) {
                        uint8_t val = pix[x + y * ctx->m.linesize];
                        sum  += val;
                        varc += val * val;
                    }
                }
            }
            varc = (varc - (((unsigned) sum * sum) >> 8) + 128) >> 8;

            ctx->mb_cmp[mb].value = varc;
            ctx->mb_cmp[mb].mb    = mb;
        }
    } else { // 10-bit
        const int linesize = ctx->m.linesize >> 1;
        for (mb_x = 0; mb_x < ctx->m.mb_width; ++mb_x) {
            uint16_t *pix = (uint16_t *)ctx->thread[0]->src[0] +
                            ((mb_y << 4) * linesize) + (mb_x << 4);
            unsigned mb  = mb_y * ctx->m.mb_width + mb_x;
            int sum = 0;
            int sqsum = 0;
            int bw = FFMIN(avctx->width - 16 * mb_x, 16);
            int bh = FFMIN((avctx->height >> ctx->interlaced) - 16 * mb_y, 16);
            int mean, sqmean;
            int i, j;
            // Macroblocks are 16x16 pixels, unlike DCT blocks which are 8x8.
            for (i = 0; i < bh; ++i) {
                for (j = 0; j < bw; ++j) {
                    // Turn 16-bit pixels into 10-bit ones.
                    const int sample = (unsigned) pix[j] >> 6;
                    sum   += sample;
                    sqsum += sample * sample;
                    // 2^10 * 2^10 * 16 * 16 = 2^28, which is less than INT_MAX
                }
                pix += linesize;
            }
            mean = sum >> 8; // 16*16 == 2^8
            sqmean = sqsum >> 8;
            ctx->mb_cmp[mb].value = sqmean - mean * mean;
            ctx->mb_cmp[mb].mb    = mb;
        }
    }
    return 0;
}