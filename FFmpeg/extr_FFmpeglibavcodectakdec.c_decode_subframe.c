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
typedef  int uint32_t ;
typedef  int int32_t ;
struct TYPE_5__ {scalar_t__ (* scalarproduct_int16 ) (int*,int*,int) ;} ;
struct TYPE_6__ {int* predictors; int* filter; int* residues; TYPE_1__ adsp; int /*<<< orphan*/  gb; } ;
typedef  TYPE_2__ TAKDecContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int FFMIN (int,int) ; 
 int FF_ARRAY_ELEMS (int*) ; 
 int MAX_PREDICTORS ; 
 int av_clip_intp2 (int,int) ; 
 int /*<<< orphan*/  decode_lpc (int*,int,int) ; 
 int decode_residues (TYPE_2__*,int*,int) ; 
 int /*<<< orphan*/  emms_c () ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_esc4 (int /*<<< orphan*/ *) ; 
 int get_sbits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int* predictor_sizes ; 
 scalar_t__ stub1 (int*,int*,int) ; 

__attribute__((used)) static int decode_subframe(TAKDecContext *s, int32_t *decoded,
                           int subframe_size, int prev_subframe_size)
{
    GetBitContext *gb = &s->gb;
    int x, y, i, j, ret = 0;
    int dshift, size, filter_quant, filter_order;
    int tfilter[MAX_PREDICTORS];

    if (!get_bits1(gb))
        return decode_residues(s, decoded, subframe_size);

    filter_order = predictor_sizes[get_bits(gb, 4)];

    if (prev_subframe_size > 0 && get_bits1(gb)) {
        if (filter_order > prev_subframe_size)
            return AVERROR_INVALIDDATA;

        decoded       -= filter_order;
        subframe_size += filter_order;

        if (filter_order > subframe_size)
            return AVERROR_INVALIDDATA;
    } else {
        int lpc_mode;

        if (filter_order > subframe_size)
            return AVERROR_INVALIDDATA;

        lpc_mode = get_bits(gb, 2);
        if (lpc_mode > 2)
            return AVERROR_INVALIDDATA;

        if ((ret = decode_residues(s, decoded, filter_order)) < 0)
            return ret;

        if (lpc_mode)
            decode_lpc(decoded, lpc_mode, filter_order);
    }

    dshift = get_bits_esc4(gb);
    size   = get_bits1(gb) + 6;

    filter_quant = 10;
    if (get_bits1(gb)) {
        filter_quant -= get_bits(gb, 3) + 1;
        if (filter_quant < 3)
            return AVERROR_INVALIDDATA;
    }

    s->predictors[0] = get_sbits(gb, 10);
    s->predictors[1] = get_sbits(gb, 10);
    s->predictors[2] = get_sbits(gb, size) * (1 << (10 - size));
    s->predictors[3] = get_sbits(gb, size) * (1 << (10 - size));
    if (filter_order > 4) {
        int tmp = size - get_bits1(gb);

        for (i = 4; i < filter_order; i++) {
            if (!(i & 3))
                x = tmp - get_bits(gb, 2);
            s->predictors[i] = get_sbits(gb, x) * (1 << (10 - size));
        }
    }

    tfilter[0] = s->predictors[0] * 64;
    for (i = 1; i < filter_order; i++) {
        uint32_t *p1 = &tfilter[0];
        uint32_t *p2 = &tfilter[i - 1];

        for (j = 0; j < (i + 1) / 2; j++) {
            x     = *p1 + ((int32_t)(s->predictors[i] * *p2 + 256) >> 9);
            *p2  += (int32_t)(s->predictors[i] * *p1 + 256) >> 9;
            *p1++ = x;
            p2--;
        }

        tfilter[i] = s->predictors[i] * 64;
    }

    x = 1 << (32 - (15 - filter_quant));
    y = 1 << ((15 - filter_quant) - 1);
    for (i = 0, j = filter_order - 1; i < filter_order / 2; i++, j--) {
        s->filter[j] = x - ((tfilter[i] + y) >> (15 - filter_quant));
        s->filter[i] = x - ((tfilter[j] + y) >> (15 - filter_quant));
    }

    if ((ret = decode_residues(s, &decoded[filter_order],
                               subframe_size - filter_order)) < 0)
        return ret;

    for (i = 0; i < filter_order; i++)
        s->residues[i] = *decoded++ >> dshift;

    y    = FF_ARRAY_ELEMS(s->residues) - filter_order;
    x    = subframe_size - filter_order;
    while (x > 0) {
        int tmp = FFMIN(y, x);

        for (i = 0; i < tmp; i++) {
            int v = 1 << (filter_quant - 1);

            if (filter_order & -16)
                v += (unsigned)s->adsp.scalarproduct_int16(&s->residues[i], s->filter,
                                                 filter_order & -16);
            for (j = filter_order & -16; j < filter_order; j += 4) {
                v += s->residues[i + j + 3] * (unsigned)s->filter[j + 3] +
                     s->residues[i + j + 2] * (unsigned)s->filter[j + 2] +
                     s->residues[i + j + 1] * (unsigned)s->filter[j + 1] +
                     s->residues[i + j    ] * (unsigned)s->filter[j    ];
            }
            v = (av_clip_intp2(v >> filter_quant, 13) * (1 << dshift)) - (unsigned)*decoded;
            *decoded++ = v;
            s->residues[filter_order + i] = v >> dshift;
        }

        x -= tmp;
        if (x > 0)
            memcpy(s->residues, &s->residues[y], 2 * filter_order);
    }

    emms_c();

    return 0;
}