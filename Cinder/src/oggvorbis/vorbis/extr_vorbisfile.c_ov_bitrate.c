#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ogg_int64_t ;
struct TYPE_6__ {scalar_t__ ready_state; int links; int* offsets; int* dataoffsets; TYPE_1__* vi; scalar_t__ seekable; } ;
struct TYPE_5__ {scalar_t__ bitrate_nominal; int bitrate_upper; int bitrate_lower; } ;
typedef  TYPE_2__ OggVorbis_File ;

/* Variables and functions */
 scalar_t__ OPENED ; 
 long OV_EINVAL ; 
 long OV_FALSE ; 
 int ov_time_total (TYPE_2__*,int) ; 
 long rint (int) ; 

long ov_bitrate(OggVorbis_File *vf,int i){
  if(vf->ready_state<OPENED)return(OV_EINVAL);
  if(i>=vf->links)return(OV_EINVAL);
  if(!vf->seekable && i!=0)return(ov_bitrate(vf,0));
  if(i<0){
    ogg_int64_t bits=0;
    int i;
    float br;
    for(i=0;i<vf->links;i++)
      bits+=(vf->offsets[i+1]-vf->dataoffsets[i])*8;
    /* This once read: return(rint(bits/ov_time_total(vf,-1)));
     * gcc 3.x on x86 miscompiled this at optimisation level 2 and above,
     * so this is slightly transformed to make it work.
     */
    br = bits/ov_time_total(vf,-1);
    return(rint(br));
  }else{
    if(vf->seekable){
      /* return the actual bitrate */
      return(rint((vf->offsets[i+1]-vf->dataoffsets[i])*8/ov_time_total(vf,i)));
    }else{
      /* return nominal if set */
      if(vf->vi[i].bitrate_nominal>0){
        return vf->vi[i].bitrate_nominal;
      }else{
        if(vf->vi[i].bitrate_upper>0){
          if(vf->vi[i].bitrate_lower>0){
            return (vf->vi[i].bitrate_upper+vf->vi[i].bitrate_lower)/2;
          }else{
            return vf->vi[i].bitrate_upper;
          }
        }
        return(OV_FALSE);
      }
    }
  }
}