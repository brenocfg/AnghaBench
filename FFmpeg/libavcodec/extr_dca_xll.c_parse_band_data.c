#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
struct TYPE_18__ {int size_in_bits; } ;
struct TYPE_17__ {int nfreqbands; } ;
struct TYPE_16__ {int nactivechsets; int* navi; int nfreqbands; int nframesegs; int nchsets; TYPE_3__ gb; TYPE_14__* avctx; TYPE_2__* chset; } ;
struct TYPE_15__ {int err_recognition; } ;
typedef  TYPE_1__ DCAXllDecoder ;
typedef  TYPE_2__ DCAXllChSet ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_EF_EXPLODE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_14__*,int /*<<< orphan*/ ,char*) ; 
 int chs_alloc_lsb_band_data (TYPE_1__*,TYPE_2__*) ; 
 int chs_alloc_msb_band_data (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  chs_clear_band_data (TYPE_1__*,TYPE_2__*,int,int) ; 
 int chs_parse_band_data (TYPE_1__*,TYPE_2__*,int,int,int) ; 
 int get_bits_count (TYPE_3__*) ; 
 int /*<<< orphan*/  skip_bits_long (TYPE_3__*,int) ; 

__attribute__((used)) static int parse_band_data(DCAXllDecoder *s)
{
    int ret, chs, seg, band, navi_pos, *navi_ptr;
    DCAXllChSet *c;

    for (chs = 0, c = s->chset; chs < s->nactivechsets; chs++, c++) {
        if ((ret = chs_alloc_msb_band_data(s, c)) < 0)
            return ret;
        if ((ret = chs_alloc_lsb_band_data(s, c)) < 0)
            return ret;
    }

    navi_pos = get_bits_count(&s->gb);
    navi_ptr = s->navi;
    for (band = 0; band < s->nfreqbands; band++) {
        for (seg = 0; seg < s->nframesegs; seg++) {
            for (chs = 0, c = s->chset; chs < s->nchsets; chs++, c++) {
                if (c->nfreqbands > band) {
                    navi_pos += *navi_ptr * 8;
                    if (navi_pos > s->gb.size_in_bits) {
                        av_log(s->avctx, AV_LOG_ERROR, "Invalid NAVI position\n");
                        return AVERROR_INVALIDDATA;
                    }
                    if (chs < s->nactivechsets &&
                        (ret = chs_parse_band_data(s, c, band, seg, navi_pos)) < 0) {
                        if (s->avctx->err_recognition & AV_EF_EXPLODE)
                            return ret;
                        chs_clear_band_data(s, c, band, seg);
                    }
                    skip_bits_long(&s->gb, navi_pos - get_bits_count(&s->gb));
                }
                navi_ptr++;
            }
        }
    }

    return 0;
}