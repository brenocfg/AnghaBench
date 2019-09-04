#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {scalar_t__* error_energy; scalar_t__* energy; } ;
struct TYPE_23__ {int framebits; int transient; int channels; TYPE_3__* block; int /*<<< orphan*/  anticollapse; scalar_t__ anticollapse_needed; scalar_t__ size; int /*<<< orphan*/  start_band; scalar_t__ pfilter; scalar_t__ silence; } ;
struct TYPE_22__ {int channels; scalar_t__** last_quantized_energy; int /*<<< orphan*/  psyctx; } ;
typedef  int /*<<< orphan*/  OpusRangeCoder ;
typedef  TYPE_1__ OpusEncContext ;
typedef  TYPE_2__ CeltFrame ;
typedef  TYPE_3__ CeltBlock ;

/* Variables and functions */
 int CELT_MAX_BANDS ; 
 int /*<<< orphan*/  celt_apply_preemph_filter (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  celt_enc_quant_pfilter (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  celt_enc_tf (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  celt_frame_mdct (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  celt_frame_setup_input (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  celt_quant_coarse (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__**) ; 
 int /*<<< orphan*/  celt_quant_final (TYPE_1__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  celt_quant_fine (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_celt_bitalloc (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_celt_quant_bands (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_opus_psy_celt_frame_init (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 scalar_t__ ff_opus_psy_celt_frame_process (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ff_opus_rc_enc_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_opus_rc_enc_log (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ff_opus_rc_put_raw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,float,int) ; 
 int opus_rc_tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void celt_encode_frame(OpusEncContext *s, OpusRangeCoder *rc,
                              CeltFrame *f, int index)
{
    ff_opus_rc_enc_init(rc);

    ff_opus_psy_celt_frame_init(&s->psyctx, f, index);

    celt_frame_setup_input(s, f);

    if (f->silence) {
        if (f->framebits >= 16)
            ff_opus_rc_enc_log(rc, 1, 15); /* Silence (if using explicit singalling) */
        for (int ch = 0; ch < s->channels; ch++)
            memset(s->last_quantized_energy[ch], 0.0f, sizeof(float)*CELT_MAX_BANDS);
        return;
    }

    /* Filters */
    celt_apply_preemph_filter(s, f);
    if (f->pfilter) {
        ff_opus_rc_enc_log(rc, 0, 15);
        celt_enc_quant_pfilter(rc, f);
    }

    /* Transform */
    celt_frame_mdct(s, f);

    /* Need to handle transient/non-transient switches at any point during analysis */
    while (ff_opus_psy_celt_frame_process(&s->psyctx, f, index))
        celt_frame_mdct(s, f);

    ff_opus_rc_enc_init(rc);

    /* Silence */
    ff_opus_rc_enc_log(rc, 0, 15);

    /* Pitch filter */
    if (!f->start_band && opus_rc_tell(rc) + 16 <= f->framebits)
        celt_enc_quant_pfilter(rc, f);

    /* Transient flag */
    if (f->size && opus_rc_tell(rc) + 3 <= f->framebits)
        ff_opus_rc_enc_log(rc, f->transient, 3);

    /* Main encoding */
    celt_quant_coarse  (f, rc, s->last_quantized_energy);
    celt_enc_tf        (f, rc);
    ff_celt_bitalloc   (f, rc, 1);
    celt_quant_fine    (f, rc);
    ff_celt_quant_bands(f, rc);

    /* Anticollapse bit */
    if (f->anticollapse_needed)
        ff_opus_rc_put_raw(rc, f->anticollapse, 1);

    /* Final per-band energy adjustments from leftover bits */
    celt_quant_final(s, rc, f);

    for (int ch = 0; ch < f->channels; ch++) {
        CeltBlock *block = &f->block[ch];
        for (int i = 0; i < CELT_MAX_BANDS; i++)
            s->last_quantized_energy[ch][i] = block->energy[i] + block->error_energy[i];
    }
}