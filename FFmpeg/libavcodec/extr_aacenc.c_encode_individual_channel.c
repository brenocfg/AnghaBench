#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  pb; TYPE_2__* coder; } ;
struct TYPE_21__ {int /*<<< orphan*/  present; } ;
struct TYPE_23__ {int* sf_idx; TYPE_1__ tns; int /*<<< orphan*/  pulse; int /*<<< orphan*/  ics; } ;
struct TYPE_22__ {int /*<<< orphan*/  (* encode_tns_info ) (TYPE_4__*,TYPE_3__*) ;int /*<<< orphan*/  (* encode_ltp_info ) (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* encode_main_pred ) (TYPE_4__*,TYPE_3__*) ;} ;
typedef  TYPE_3__ SingleChannelElement ;
typedef  int /*<<< orphan*/  AVCodecContext ;
typedef  TYPE_4__ AACEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  encode_band_info (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  encode_pulses (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encode_scale_factors (int /*<<< orphan*/ *,TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  encode_spectral_coeffs (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_ics_info (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*,TYPE_3__*) ; 

__attribute__((used)) static int encode_individual_channel(AVCodecContext *avctx, AACEncContext *s,
                                     SingleChannelElement *sce,
                                     int common_window)
{
    put_bits(&s->pb, 8, sce->sf_idx[0]);
    if (!common_window) {
        put_ics_info(s, &sce->ics);
        if (s->coder->encode_main_pred)
            s->coder->encode_main_pred(s, sce);
        if (s->coder->encode_ltp_info)
            s->coder->encode_ltp_info(s, sce, 0);
    }
    encode_band_info(s, sce);
    encode_scale_factors(avctx, s, sce);
    encode_pulses(s, &sce->pulse);
    put_bits(&s->pb, 1, !!sce->tns.present);
    if (s->coder->encode_tns_info)
        s->coder->encode_tns_info(s, sce);
    put_bits(&s->pb, 1, 0); //ssr
    encode_spectral_coeffs(s, sce);
    return 0;
}