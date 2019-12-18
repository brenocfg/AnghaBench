#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int* noisecompand; } ;
typedef  TYPE_1__ vorbis_info_psy ;
struct TYPE_8__ {TYPE_4__* codec_setup; } ;
typedef  TYPE_2__ vorbis_info ;
struct TYPE_9__ {int* data; } ;
typedef  TYPE_3__ compandblock ;
struct TYPE_10__ {TYPE_1__** psy_param; } ;
typedef  TYPE_4__ codec_setup_info ;

/* Variables and functions */
 int NOISE_COMPAND_LEVELS ; 

__attribute__((used)) static void vorbis_encode_compand_setup(vorbis_info *vi,double s,int block,
                                        const compandblock *in,
                                        const double *x){
  int i,is=s;
  double ds=s-is;
  codec_setup_info *ci=vi->codec_setup;
  vorbis_info_psy *p=ci->psy_param[block];

  ds=x[is]*(1.-ds)+x[is+1]*ds;
  is=(int)ds;
  ds-=is;
  if(ds==0 && is>0){
    is--;
    ds=1.;
  }

  /* interpolate the compander settings */
  for(i=0;i<NOISE_COMPAND_LEVELS;i++)
    p->noisecompand[i]=in[is].data[i]*(1.-ds)+in[is+1].data[i]*ds;
  return;
}