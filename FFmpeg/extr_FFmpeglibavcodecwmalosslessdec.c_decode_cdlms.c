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
struct TYPE_5__ {int num_channels; int* cdlms_ttl; int bits_per_sample; TYPE_1__** cdlms; int /*<<< orphan*/  gb; int /*<<< orphan*/  avctx; } ;
typedef  TYPE_2__ WmallDecodeCtx ;
struct TYPE_4__ {int order; int scaling; int coefsend; int bitsend; int* coefs; } ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int MAX_ORDER ; 
 int /*<<< orphan*/  WMALL_COEFF_PAD_SIZE ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int av_log2 (int) ; 
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ ,char*,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bitsz (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_cdlms(WmallDecodeCtx *s)
{
    int c, i;
    int cdlms_send_coef = get_bits1(&s->gb);

    for (c = 0; c < s->num_channels; c++) {
        s->cdlms_ttl[c] = get_bits(&s->gb, 3) + 1;
        for (i = 0; i < s->cdlms_ttl[c]; i++) {
            s->cdlms[c][i].order = (get_bits(&s->gb, 7) + 1) * 8;
            if (s->cdlms[c][i].order > MAX_ORDER) {
                av_log(s->avctx, AV_LOG_ERROR,
                       "Order[%d][%d] %d > max (%d), not supported\n",
                       c, i, s->cdlms[c][i].order, MAX_ORDER);
                s->cdlms[0][0].order = 0;
                return AVERROR_INVALIDDATA;
            }
            if(s->cdlms[c][i].order & 8 && s->bits_per_sample == 16) {
                static int warned;
                if(!warned)
                    avpriv_request_sample(s->avctx, "CDLMS of order %d",
                                          s->cdlms[c][i].order);
                warned = 1;
            }
        }

        for (i = 0; i < s->cdlms_ttl[c]; i++)
            s->cdlms[c][i].scaling = get_bits(&s->gb, 4);

        if (cdlms_send_coef) {
            for (i = 0; i < s->cdlms_ttl[c]; i++) {
                int cbits, shift_l, shift_r, j;
                cbits = av_log2(s->cdlms[c][i].order);
                if ((1 << cbits) < s->cdlms[c][i].order)
                    cbits++;
                s->cdlms[c][i].coefsend = get_bits(&s->gb, cbits) + 1;

                cbits = av_log2(s->cdlms[c][i].scaling + 1);
                if ((1 << cbits) < s->cdlms[c][i].scaling + 1)
                    cbits++;

                s->cdlms[c][i].bitsend = get_bitsz(&s->gb, cbits) + 2;
                shift_l = 32 - s->cdlms[c][i].bitsend;
                shift_r = 32 - s->cdlms[c][i].scaling - 2;
                for (j = 0; j < s->cdlms[c][i].coefsend; j++)
                    s->cdlms[c][i].coefs[j] =
                        (get_bits(&s->gb, s->cdlms[c][i].bitsend) << shift_l) >> shift_r;
            }
        }

        for (i = 0; i < s->cdlms_ttl[c]; i++)
            memset(s->cdlms[c][i].coefs + s->cdlms[c][i].order,
                   0, WMALL_COEFF_PAD_SIZE);
    }

    return 0;
}