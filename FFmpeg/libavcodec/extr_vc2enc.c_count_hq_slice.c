#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  dwtcoef ;
struct TYPE_7__ {int prefix_bytes; int wavelet_depth; int** qmagic_lut; int num_x; int num_y; int size_scaler; TYPE_1__* plane; scalar_t__** quant; } ;
typedef  TYPE_2__ VC2EncContext ;
struct TYPE_9__ {int* cache; int x; int y; TYPE_2__* ctx; } ;
struct TYPE_8__ {int width; int height; int const stride; int /*<<< orphan*/ * buf; } ;
struct TYPE_6__ {TYPE_3__** band; } ;
typedef  TYPE_3__ SubBand ;
typedef  TYPE_4__ SliceArgs ;

/* Variables and functions */
 int /*<<< orphan*/  FFABS (int /*<<< orphan*/ ) ; 
 int FFALIGN (int,int) ; 
 int FFMAX (scalar_t__,int /*<<< orphan*/ ) ; 
 int MAX_DWT_LEVELS ; 
 int /*<<< orphan*/  QUANT (int /*<<< orphan*/ ,int const,int const,int const) ; 
 int av_log2 (int /*<<< orphan*/ ) ; 
 scalar_t__ count_vc2_ue_uint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ff_dirac_qscale_tab ; 

__attribute__((used)) static int count_hq_slice(SliceArgs *slice, int quant_idx)
{
    int x, y;
    uint8_t quants[MAX_DWT_LEVELS][4];
    int bits = 0, p, level, orientation;
    VC2EncContext *s = slice->ctx;

    if (slice->cache[quant_idx])
        return slice->cache[quant_idx];

    bits += 8*s->prefix_bytes;
    bits += 8; /* quant_idx */

    for (level = 0; level < s->wavelet_depth; level++)
        for (orientation = !!level; orientation < 4; orientation++)
            quants[level][orientation] = FFMAX(quant_idx - s->quant[level][orientation], 0);

    for (p = 0; p < 3; p++) {
        int bytes_start, bytes_len, pad_s, pad_c;
        bytes_start = bits >> 3;
        bits += 8;
        for (level = 0; level < s->wavelet_depth; level++) {
            for (orientation = !!level; orientation < 4; orientation++) {
                SubBand *b = &s->plane[p].band[level][orientation];

                const int q_idx = quants[level][orientation];
                const uint64_t q_m = ((uint64_t)s->qmagic_lut[q_idx][0]) << 2;
                const uint64_t q_a = s->qmagic_lut[q_idx][1];
                const int q_s = av_log2(ff_dirac_qscale_tab[q_idx]) + 32;

                const int left   = b->width  * slice->x    / s->num_x;
                const int right  = b->width  *(slice->x+1) / s->num_x;
                const int top    = b->height * slice->y    / s->num_y;
                const int bottom = b->height *(slice->y+1) / s->num_y;

                dwtcoef *buf = b->buf + top * b->stride;

                for (y = top; y < bottom; y++) {
                    for (x = left; x < right; x++) {
                        uint32_t c_abs = QUANT(FFABS(buf[x]), q_m, q_a, q_s);
                        bits += count_vc2_ue_uint(c_abs);
                        bits += !!c_abs;
                    }
                    buf += b->stride;
                }
            }
        }
        bits += FFALIGN(bits, 8) - bits;
        bytes_len = (bits >> 3) - bytes_start - 1;
        pad_s = FFALIGN(bytes_len, s->size_scaler)/s->size_scaler;
        pad_c = (pad_s*s->size_scaler) - bytes_len;
        bits += pad_c*8;
    }

    slice->cache[quant_idx] = bits;

    return bits;
}