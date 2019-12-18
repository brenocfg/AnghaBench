#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {long channels; long rate; scalar_t__ version; TYPE_5__* codec_setup; } ;
typedef  TYPE_2__ vorbis_info ;
struct TYPE_9__ {int* psy_lowpass; int* psy_ath_float; int* psy_ath_abs; } ;
typedef  TYPE_3__ ve_setup_data_template ;
struct TYPE_10__ {int impulse_block_p; int noise_normalize_p; int base_setting; int stereo_point_setting; int lowpass_kHz; int ath_floating_dB; int ath_absolute_dB; int amplitude_track_dBpersec; int trigger_setting; TYPE_1__* block; int /*<<< orphan*/  lowpass_altered; TYPE_3__* setup; } ;
typedef  TYPE_4__ highlevel_encode_setup ;
struct TYPE_11__ {TYPE_4__ hi; } ;
typedef  TYPE_5__ codec_setup_info ;
struct TYPE_7__ {int tone_mask_setting; int tone_peaklimit_setting; int noise_bias_setting; int noise_compand_setting; } ;

/* Variables and functions */

__attribute__((used)) static void vorbis_encode_setup_setting(vorbis_info *vi,
                                       long  channels,
                                       long  rate){
  int i,is;
  codec_setup_info *ci=vi->codec_setup;
  highlevel_encode_setup *hi=&ci->hi;
  const ve_setup_data_template *setup=hi->setup;
  double ds;

  vi->version=0;
  vi->channels=channels;
  vi->rate=rate;

  hi->impulse_block_p=1;
  hi->noise_normalize_p=1;

  is=hi->base_setting;
  ds=hi->base_setting-is;

  hi->stereo_point_setting=hi->base_setting;

  if(!hi->lowpass_altered)
    hi->lowpass_kHz=
      setup->psy_lowpass[is]*(1.-ds)+setup->psy_lowpass[is+1]*ds;

  hi->ath_floating_dB=setup->psy_ath_float[is]*(1.-ds)+
    setup->psy_ath_float[is+1]*ds;
  hi->ath_absolute_dB=setup->psy_ath_abs[is]*(1.-ds)+
    setup->psy_ath_abs[is+1]*ds;

  hi->amplitude_track_dBpersec=-6.;
  hi->trigger_setting=hi->base_setting;

  for(i=0;i<4;i++){
    hi->block[i].tone_mask_setting=hi->base_setting;
    hi->block[i].tone_peaklimit_setting=hi->base_setting;
    hi->block[i].noise_bias_setting=hi->base_setting;
    hi->block[i].noise_compand_setting=hi->base_setting;
  }
}