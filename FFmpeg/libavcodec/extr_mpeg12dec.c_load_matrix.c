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
typedef  int uint16_t ;
struct TYPE_4__ {int* idct_permutation; } ;
struct TYPE_5__ {int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; TYPE_1__ idsp; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 size_t* ff_zigzag_direct ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int load_matrix(MpegEncContext *s, uint16_t matrix0[64],
                       uint16_t matrix1[64], int intra)
{
    int i;

    for (i = 0; i < 64; i++) {
        int j = s->idsp.idct_permutation[ff_zigzag_direct[i]];
        int v = get_bits(&s->gb, 8);
        if (v == 0) {
            av_log(s->avctx, AV_LOG_ERROR, "matrix damaged\n");
            return AVERROR_INVALIDDATA;
        }
        if (intra && i == 0 && v != 8) {
            av_log(s->avctx, AV_LOG_DEBUG, "intra matrix specifies invalid DC quantizer %d, ignoring\n", v);
            v = 8; // needed by pink.mpg / issue1046
        }
        matrix0[j] = v;
        if (matrix1)
            matrix1[j] = v;
    }
    return 0;
}