#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int* preecho_thresh; int* postecho_thresh; int /*<<< orphan*/  ampmax_att_per_sec; } ;
typedef  TYPE_2__ vorbis_info_psy_global ;
struct TYPE_11__ {TYPE_4__* codec_setup; } ;
typedef  TYPE_3__ vorbis_info ;
struct TYPE_9__ {int /*<<< orphan*/  amplitude_track_dBpersec; } ;
struct TYPE_12__ {TYPE_1__ hi; TYPE_2__ psy_g_param; } ;
typedef  TYPE_4__ codec_setup_info ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__ const*,int) ; 

__attribute__((used)) static void vorbis_encode_global_psych_setup(vorbis_info *vi,double s,
                                            const vorbis_info_psy_global *in,
                                            const double *x){
  int i,is=s;
  double ds=s-is;
  codec_setup_info *ci=vi->codec_setup;
  vorbis_info_psy_global *g=&ci->psy_g_param;

  memcpy(g,in+(int)x[is],sizeof(*g));

  ds=x[is]*(1.-ds)+x[is+1]*ds;
  is=(int)ds;
  ds-=is;
  if(ds==0 && is>0){
    is--;
    ds=1.;
  }

  /* interpolate the trigger threshholds */
  for(i=0;i<4;i++){
    g->preecho_thresh[i]=in[is].preecho_thresh[i]*(1.-ds)+in[is+1].preecho_thresh[i]*ds;
    g->postecho_thresh[i]=in[is].postecho_thresh[i]*(1.-ds)+in[is+1].postecho_thresh[i]*ds;
  }
  g->ampmax_att_per_sec=ci->hi.amplitude_track_dBpersec;
  return;
}