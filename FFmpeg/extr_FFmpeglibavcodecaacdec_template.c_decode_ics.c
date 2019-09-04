#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {void* present; } ;
typedef  TYPE_3__ TemporalNoiseShaping ;
struct TYPE_32__ {int warned_gain_control; TYPE_2__* oc; int /*<<< orphan*/  avctx; } ;
struct TYPE_31__ {scalar_t__* window_sequence; int /*<<< orphan*/  num_swb; int /*<<< orphan*/  swb_offset; } ;
struct TYPE_30__ {scalar_t__ num_pulse; } ;
struct TYPE_29__ {int /*<<< orphan*/  band_type; int /*<<< orphan*/  sf; int /*<<< orphan*/  band_type_run_end; int /*<<< orphan*/ * coeffs; TYPE_6__ ics; TYPE_3__ tns; } ;
struct TYPE_26__ {scalar_t__ object_type; } ;
struct TYPE_27__ {TYPE_1__ m4ac; } ;
typedef  TYPE_4__ SingleChannelElement ;
typedef  TYPE_5__ Pulse ;
typedef  TYPE_6__ IndividualChannelStream ;
typedef  int /*<<< orphan*/  INTFLOAT ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_7__ AACContext ;

/* Variables and functions */
 scalar_t__ AOT_AAC_MAIN ; 
 scalar_t__ AOT_ER_AAC_ELD ; 
 scalar_t__ AOT_ER_AAC_LC ; 
 scalar_t__ AOT_ER_AAC_LD ; 
 scalar_t__ AOT_ER_AAC_LTP ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ EIGHT_SHORT_SEQUENCE ; 
 int /*<<< orphan*/  apply_prediction (TYPE_7__*,TYPE_4__*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (int /*<<< orphan*/ ,char*) ; 
 int decode_band_types (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  decode_gain_control (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int decode_ics_info (TYPE_7__*,TYPE_6__*,int /*<<< orphan*/ *) ; 
 scalar_t__ decode_pulses (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int decode_scalefactors (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int decode_spectrum_and_dequant (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_5__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int decode_tns (TYPE_7__*,TYPE_3__*,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_ics(AACContext *ac, SingleChannelElement *sce,
                      GetBitContext *gb, int common_window, int scale_flag)
{
    Pulse pulse;
    TemporalNoiseShaping    *tns = &sce->tns;
    IndividualChannelStream *ics = &sce->ics;
    INTFLOAT *out = sce->coeffs;
    int global_gain, eld_syntax, er_syntax, pulse_present = 0;
    int ret;

    eld_syntax = ac->oc[1].m4ac.object_type == AOT_ER_AAC_ELD;
    er_syntax  = ac->oc[1].m4ac.object_type == AOT_ER_AAC_LC ||
                 ac->oc[1].m4ac.object_type == AOT_ER_AAC_LTP ||
                 ac->oc[1].m4ac.object_type == AOT_ER_AAC_LD ||
                 ac->oc[1].m4ac.object_type == AOT_ER_AAC_ELD;

    /* This assignment is to silence a GCC warning about the variable being used
     * uninitialized when in fact it always is.
     */
    pulse.num_pulse = 0;

    global_gain = get_bits(gb, 8);

    if (!common_window && !scale_flag) {
        ret = decode_ics_info(ac, ics, gb);
        if (ret < 0)
            goto fail;
    }

    if ((ret = decode_band_types(ac, sce->band_type,
                                 sce->band_type_run_end, gb, ics)) < 0)
        goto fail;
    if ((ret = decode_scalefactors(ac, sce->sf, gb, global_gain, ics,
                                  sce->band_type, sce->band_type_run_end)) < 0)
        goto fail;

    pulse_present = 0;
    if (!scale_flag) {
        if (!eld_syntax && (pulse_present = get_bits1(gb))) {
            if (ics->window_sequence[0] == EIGHT_SHORT_SEQUENCE) {
                av_log(ac->avctx, AV_LOG_ERROR,
                       "Pulse tool not allowed in eight short sequence.\n");
                ret = AVERROR_INVALIDDATA;
                goto fail;
            }
            if (decode_pulses(&pulse, gb, ics->swb_offset, ics->num_swb)) {
                av_log(ac->avctx, AV_LOG_ERROR,
                       "Pulse data corrupt or invalid.\n");
                ret = AVERROR_INVALIDDATA;
                goto fail;
            }
        }
        tns->present = get_bits1(gb);
        if (tns->present && !er_syntax) {
            ret = decode_tns(ac, tns, gb, ics);
            if (ret < 0)
                goto fail;
        }
        if (!eld_syntax && get_bits1(gb)) {
            decode_gain_control(sce, gb);
            if (!ac->warned_gain_control) {
                avpriv_report_missing_feature(ac->avctx, "Gain control");
                ac->warned_gain_control = 1;
            }
        }
        // I see no textual basis in the spec for this occurring after SSR gain
        // control, but this is what both reference and real implmentations do
        if (tns->present && er_syntax) {
            ret = decode_tns(ac, tns, gb, ics);
            if (ret < 0)
                goto fail;
        }
    }

    ret = decode_spectrum_and_dequant(ac, out, gb, sce->sf, pulse_present,
                                    &pulse, ics, sce->band_type);
    if (ret < 0)
        goto fail;

    if (ac->oc[1].m4ac.object_type == AOT_AAC_MAIN && !common_window)
        apply_prediction(ac, sce);

    return 0;
fail:
    tns->present = 0;
    return ret;
}