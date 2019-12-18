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
struct TYPE_6__ {size_t dmix_type; int hier_ofs; int* dmix_coeff; int* dmix_scale; int* dmix_scale_inv; int nchannels; scalar_t__ primary_chset; } ;
struct TYPE_5__ {int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ DCAXllDecoder ;
typedef  TYPE_2__ DCAXllChSet ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FF_DCA_DMIXTABLE_OFFSET ; 
 unsigned int FF_DCA_DMIXTABLE_SIZE ; 
 unsigned int FF_DCA_INV_DMIXTABLE_SIZE ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int* ff_dca_dmix_primary_nch ; 
 int* ff_dca_dmixtable ; 
 int* ff_dca_inv_dmixtable ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int mul16 (int,int) ; 

__attribute__((used)) static int parse_dmix_coeffs(DCAXllDecoder *s, DCAXllChSet *c)
{
    // Size of downmix coefficient matrix
    int m = c->primary_chset ? ff_dca_dmix_primary_nch[c->dmix_type] : c->hier_ofs;
    int i, j, *coeff_ptr = c->dmix_coeff;

    for (i = 0; i < m; i++) {
        int code, sign, coeff, scale, scale_inv = 0;
        unsigned int index;

        // Downmix scale (only for non-primary channel sets)
        if (!c->primary_chset) {
            code = get_bits(&s->gb, 9);
            sign = (code >> 8) - 1;
            index = (code & 0xff) - FF_DCA_DMIXTABLE_OFFSET;
            if (index >= FF_DCA_INV_DMIXTABLE_SIZE) {
                av_log(s->avctx, AV_LOG_ERROR, "Invalid XLL downmix scale index\n");
                return AVERROR_INVALIDDATA;
            }
            scale = ff_dca_dmixtable[index + FF_DCA_DMIXTABLE_OFFSET];
            scale_inv = ff_dca_inv_dmixtable[index];
            c->dmix_scale[i] = (scale ^ sign) - sign;
            c->dmix_scale_inv[i] = (scale_inv ^ sign) - sign;
        }

        // Downmix coefficients
        for (j = 0; j < c->nchannels; j++) {
            code = get_bits(&s->gb, 9);
            sign = (code >> 8) - 1;
            index = code & 0xff;
            if (index >= FF_DCA_DMIXTABLE_SIZE) {
                av_log(s->avctx, AV_LOG_ERROR, "Invalid XLL downmix coefficient index\n");
                return AVERROR_INVALIDDATA;
            }
            coeff = ff_dca_dmixtable[index];
            if (!c->primary_chset)
                // Multiply by |InvDmixScale| to get |UndoDmixScale|
                coeff = mul16(scale_inv, coeff);
            *coeff_ptr++ = (coeff ^ sign) - sign;
        }
    }

    return 0;
}