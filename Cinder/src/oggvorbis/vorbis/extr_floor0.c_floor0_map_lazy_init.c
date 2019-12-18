#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int** linearmap; float ln; int* n; } ;
typedef  TYPE_1__ vorbis_look_floor0 ;
struct TYPE_10__ {float rate; } ;
typedef  TYPE_2__ vorbis_info_floor0 ;
typedef  int /*<<< orphan*/  vorbis_info_floor ;
struct TYPE_11__ {TYPE_6__* codec_setup; } ;
typedef  TYPE_3__ vorbis_info ;
struct TYPE_12__ {TYPE_3__* vi; } ;
typedef  TYPE_4__ vorbis_dsp_state ;
struct TYPE_13__ {size_t W; TYPE_4__* vd; } ;
typedef  TYPE_5__ vorbis_block ;
struct TYPE_14__ {int* blocksizes; } ;
typedef  TYPE_6__ codec_setup_info ;

/* Variables and functions */
 int* _ogg_malloc (int) ; 
 int floor (float) ; 
 float toBARK (float) ; 

__attribute__((used)) static void floor0_map_lazy_init(vorbis_block      *vb,
                                 vorbis_info_floor *infoX,
                                 vorbis_look_floor0 *look){
  if(!look->linearmap[vb->W]){
    vorbis_dsp_state   *vd=vb->vd;
    vorbis_info        *vi=vd->vi;
    codec_setup_info   *ci=vi->codec_setup;
    vorbis_info_floor0 *info=(vorbis_info_floor0 *)infoX;
    int W=vb->W;
    int n=ci->blocksizes[W]/2,j;

    /* we choose a scaling constant so that:
       floor(bark(rate/2-1)*C)=mapped-1
     floor(bark(rate/2)*C)=mapped */
    float scale=look->ln/toBARK(info->rate/2.f);

    /* the mapping from a linear scale to a smaller bark scale is
       straightforward.  We do *not* make sure that the linear mapping
       does not skip bark-scale bins; the decoder simply skips them and
       the encoder may do what it wishes in filling them.  They're
       necessary in some mapping combinations to keep the scale spacing
       accurate */
    look->linearmap[W]=_ogg_malloc((n+1)*sizeof(**look->linearmap));
    for(j=0;j<n;j++){
      int val=floor( toBARK((info->rate/2.f)/n*j)
                     *scale); /* bark numbers represent band edges */
      if(val>=look->ln)val=look->ln-1; /* guard against the approximation */
      look->linearmap[W][j]=val;
    }
    look->linearmap[W][j]=-1;
    look->n[W]=n;
  }
}