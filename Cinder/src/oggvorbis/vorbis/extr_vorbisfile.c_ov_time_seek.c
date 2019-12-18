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
struct TYPE_7__ {scalar_t__ ready_state; int links; TYPE_1__* vi; scalar_t__* pcmlengths; int /*<<< orphan*/  seekable; } ;
struct TYPE_6__ {double rate; } ;
typedef  TYPE_2__ OggVorbis_File ;

/* Variables and functions */
 scalar_t__ OPENED ; 
 int OV_EINVAL ; 
 int OV_ENOSEEK ; 
 int ov_pcm_seek (TYPE_2__*,scalar_t__) ; 
 double ov_time_total (TYPE_2__*,int) ; 

int ov_time_seek(OggVorbis_File *vf,double seconds){
  /* translate time to PCM position and call ov_pcm_seek */

  int link=-1;
  ogg_int64_t pcm_total=0;
  double time_total=0.;

  if(vf->ready_state<OPENED)return(OV_EINVAL);
  if(!vf->seekable)return(OV_ENOSEEK);
  if(seconds<0)return(OV_EINVAL);

  /* which bitstream section does this time offset occur in? */
  for(link=0;link<vf->links;link++){
    double addsec = ov_time_total(vf,link);
    if(seconds<time_total+addsec)break;
    time_total+=addsec;
    pcm_total+=vf->pcmlengths[link*2+1];
  }

  if(link==vf->links)return(OV_EINVAL);

  /* enough information to convert time offset to pcm offset */
  {
    ogg_int64_t target=pcm_total+(seconds-time_total)*vf->vi[link].rate;
    return(ov_pcm_seek(vf,target));
  }
}