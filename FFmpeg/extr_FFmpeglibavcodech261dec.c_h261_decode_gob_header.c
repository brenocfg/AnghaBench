#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int err_recognition; } ;
struct TYPE_5__ {scalar_t__ qscale; int mb_height; TYPE_4__* avctx; int /*<<< orphan*/  gb; } ;
struct TYPE_6__ {int gob_number; scalar_t__ mba_diff; scalar_t__ current_mba; scalar_t__ gob_start_code_skipped; TYPE_1__ s; } ;
typedef  TYPE_1__ MpegEncContext ;
typedef  TYPE_2__ H261Context ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_EF_BITSTREAM ; 
 int AV_EF_COMPLIANT ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 unsigned int show_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ skip_1stop_8data_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int h261_decode_gob_header(H261Context *h)
{
    unsigned int val;
    MpegEncContext *const s = &h->s;

    if (!h->gob_start_code_skipped) {
        /* Check for GOB Start Code */
        val = show_bits(&s->gb, 15);
        if (val)
            return -1;

        /* We have a GBSC */
        skip_bits(&s->gb, 16);
    }

    h->gob_start_code_skipped = 0;

    h->gob_number = get_bits(&s->gb, 4); /* GN */
    s->qscale     = get_bits(&s->gb, 5); /* GQUANT */

    /* Check if gob_number is valid */
    if (s->mb_height == 18) { // CIF
        if ((h->gob_number <= 0) || (h->gob_number > 12))
            return -1;
    } else { // QCIF
        if ((h->gob_number != 1) && (h->gob_number != 3) &&
            (h->gob_number != 5))
            return -1;
    }

    /* GEI */
    if (skip_1stop_8data_bits(&s->gb) < 0)
        return AVERROR_INVALIDDATA;

    if (s->qscale == 0) {
        av_log(s->avctx, AV_LOG_ERROR, "qscale has forbidden 0 value\n");
        if (s->avctx->err_recognition & (AV_EF_BITSTREAM | AV_EF_COMPLIANT))
            return -1;
    }

    /* For the first transmitted macroblock in a GOB, MBA is the absolute
     * address. For subsequent macroblocks, MBA is the difference between
     * the absolute addresses of the macroblock and the last transmitted
     * macroblock. */
    h->current_mba = 0;
    h->mba_diff    = 0;

    return 0;
}