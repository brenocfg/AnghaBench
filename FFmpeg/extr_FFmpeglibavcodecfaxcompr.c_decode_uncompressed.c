#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int av_log2 (int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int show_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_uncompressed(AVCodecContext *avctx, GetBitContext *gb,
                               unsigned int *pix_left, int **runs,
                               const int *runend, int *mode)
{
    int eob = 0;
    int newmode;
    int saved_run = 0;

    do {
        int cwi, k;
        int cw = 0;
        int codes[2];
        do {
            cwi = show_bits(gb, 11);
            if (!cwi) {
                av_log(avctx, AV_LOG_ERROR, "Invalid uncompressed codeword\n");
                return AVERROR_INVALIDDATA;
            }
            cwi = 10 - av_log2(cwi);
            skip_bits(gb, cwi + 1);
            if (cwi > 5) {
                newmode = get_bits1(gb);
                eob = 1;
                cwi -= 6;
            }
            cw += cwi;
        } while(cwi == 5);

        codes[0] = cw;
        codes[1] = !eob;

        for (k = 0; k < 2; k++) {
            if (codes[k]) {
                if (*mode == !k) {
                    *(*runs)++ = saved_run;
                    if (*runs >= runend) {
                        av_log(avctx, AV_LOG_ERROR, "uncompressed run overrun\n");
                        return AVERROR_INVALIDDATA;
                    }
                    if (*pix_left <= saved_run) {
                        av_log(avctx, AV_LOG_ERROR, "uncompressed run went out of bounds\n");
                        return AVERROR_INVALIDDATA;
                    }
                    *pix_left -= saved_run;
                    saved_run = 0;
                    *mode = !*mode;
                }
                saved_run += codes[k];
            }
        }
    } while (!eob);
    *(*runs)++ = saved_run;
    if (*runs >= runend) {
        av_log(avctx, AV_LOG_ERROR, "uncompressed run overrun\n");
        return AVERROR_INVALIDDATA;
    }
    if (*pix_left <= saved_run) {
        if (*pix_left == saved_run)
            return 1;
        av_log(avctx, AV_LOG_ERROR, "uncompressed run went out of boundsE\n");
        return AVERROR_INVALIDDATA;
    }
    *pix_left -= saved_run;
    saved_run = 0;
    *mode = !*mode;
    if (newmode != *mode) { //FIXME CHECK
        *(*runs)++ = 0;
        if (*runs >= runend) {
            av_log(avctx, AV_LOG_ERROR, "uncompressed run overrun\n");
            return AVERROR_INVALIDDATA;
        }
        *mode = newmode;
    }
    return 0;
}