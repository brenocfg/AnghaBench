#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int n; int ln; int* linearmap; int /*<<< orphan*/ * lsp_look; TYPE_4__* vi; int /*<<< orphan*/  m; } ;
typedef  TYPE_1__ vorbis_look_floor0 ;
typedef  TYPE_1__ vorbis_look_floor ;
struct TYPE_12__ {size_t blockflag; } ;
typedef  TYPE_3__ vorbis_info_mode ;
struct TYPE_13__ {int barkmap; int rate; int /*<<< orphan*/  order; } ;
typedef  TYPE_4__ vorbis_info_floor0 ;
typedef  int /*<<< orphan*/  vorbis_info_floor ;
struct TYPE_14__ {scalar_t__ codec_setup; } ;
typedef  TYPE_5__ vorbis_info ;
struct TYPE_15__ {TYPE_5__* vi; } ;
typedef  TYPE_6__ vorbis_dsp_state ;
typedef  int /*<<< orphan*/  ogg_int32_t ;
struct TYPE_16__ {int* blocksizes; } ;
typedef  TYPE_7__ codec_setup_info ;

/* Variables and functions */
 scalar_t__ _ogg_calloc (int,int) ; 
 scalar_t__ _ogg_malloc (int) ; 
 int toBARK (int) ; 
 int /*<<< orphan*/  vorbis_coslook2_i (int) ; 

__attribute__((used)) static vorbis_look_floor *floor0_look (vorbis_dsp_state *vd,vorbis_info_mode *mi,
                              vorbis_info_floor *i){
  int j;
  vorbis_info        *vi=vd->vi;
  codec_setup_info   *ci=(codec_setup_info *)vi->codec_setup;
  vorbis_info_floor0 *info=(vorbis_info_floor0 *)i;
  vorbis_look_floor0 *look=(vorbis_look_floor0 *)_ogg_calloc(1,sizeof(*look));
  look->m=info->order;
  look->n=ci->blocksizes[mi->blockflag]/2;
  look->ln=info->barkmap;
  look->vi=info;

  /* the mapping from a linear scale to a smaller bark scale is
     straightforward.  We do *not* make sure that the linear mapping
     does not skip bark-scale bins; the decoder simply skips them and
     the encoder may do what it wishes in filling them.  They're
     necessary in some mapping combinations to keep the scale spacing
     accurate */
  look->linearmap=(int *)_ogg_malloc((look->n+1)*sizeof(*look->linearmap));
  for(j=0;j<look->n;j++){

    int val=(look->ln*
	     ((toBARK(info->rate/2*j/look->n)<<11)/toBARK(info->rate/2)))>>11;

    if(val>=look->ln)val=look->ln-1; /* guard against the approximation */
    look->linearmap[j]=val;
  }
  look->linearmap[j]=-1;

  look->lsp_look=(ogg_int32_t *)_ogg_malloc(look->ln*sizeof(*look->lsp_look));
  for(j=0;j<look->ln;j++)
    look->lsp_look[j]=vorbis_coslook2_i(0x10000*j/look->ln);

  return look;
}