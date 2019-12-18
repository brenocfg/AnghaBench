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
struct TYPE_6__ {float ampmax_att_per_sec; } ;
typedef  TYPE_1__ vorbis_info_psy_global ;
struct TYPE_7__ {float rate; TYPE_4__* codec_setup; } ;
typedef  TYPE_2__ vorbis_info ;
struct TYPE_8__ {size_t W; TYPE_2__* vi; } ;
typedef  TYPE_3__ vorbis_dsp_state ;
struct TYPE_9__ {int* blocksizes; TYPE_1__ psy_g_param; } ;
typedef  TYPE_4__ codec_setup_info ;

/* Variables and functions */

float _vp_ampmax_decay(float amp,vorbis_dsp_state *vd){
  vorbis_info *vi=vd->vi;
  codec_setup_info *ci=vi->codec_setup;
  vorbis_info_psy_global *gi=&ci->psy_g_param;

  int n=ci->blocksizes[vd->W]/2;
  float secs=(float)n/vi->rate;

  amp+=secs*gi->ampmax_att_per_sec;
  if(amp<-9999)amp=-9999;
  return(amp);
}