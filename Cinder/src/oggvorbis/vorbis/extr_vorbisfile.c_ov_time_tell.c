#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ogg_int64_t ;
struct TYPE_7__ {scalar_t__ ready_state; int links; scalar_t__* pcmlengths; scalar_t__ pcm_offset; TYPE_1__* vi; scalar_t__ seekable; } ;
struct TYPE_6__ {double rate; } ;
typedef  TYPE_2__ OggVorbis_File ;

/* Variables and functions */
 scalar_t__ OPENED ; 
 double OV_EINVAL ; 
 scalar_t__ ov_pcm_total (TYPE_2__*,int) ; 
 double ov_time_total (TYPE_2__*,int) ; 

double ov_time_tell(OggVorbis_File *vf){
  int link=0;
  ogg_int64_t pcm_total=0;
  double time_total=0.f;

  if(vf->ready_state<OPENED)return(OV_EINVAL);
  if(vf->seekable){
    pcm_total=ov_pcm_total(vf,-1);
    time_total=ov_time_total(vf,-1);

    /* which bitstream section does this time offset occur in? */
    for(link=vf->links-1;link>=0;link--){
      pcm_total-=vf->pcmlengths[link*2+1];
      time_total-=ov_time_total(vf,link);
      if(vf->pcm_offset>=pcm_total)break;
    }
  }

  return((double)time_total+(double)(vf->pcm_offset-pcm_total)/vf->vi[link].rate);
}