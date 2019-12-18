#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int current_link; scalar_t__ ready_state; long samptrack; long bittrack; TYPE_1__* vi; scalar_t__ seekable; } ;
struct TYPE_4__ {long rate; } ;
typedef  TYPE_2__ OggVorbis_File ;

/* Variables and functions */
 scalar_t__ OPENED ; 
 long OV_EINVAL ; 
 long OV_FALSE ; 

long ov_bitrate_instant(OggVorbis_File *vf){
  int link=(vf->seekable?vf->current_link:0);
  long ret;
  if(vf->ready_state<OPENED)return(OV_EINVAL);
  if(vf->samptrack==0)return(OV_FALSE);
  ret=vf->bittrack/vf->samptrack*vf->vi[link].rate;
  vf->bittrack=0;
  vf->samptrack=0;
  return(ret);
}