#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ready_state; } ;
typedef  TYPE_1__ OggVorbis_File ;

/* Variables and functions */
 int OV_EINVAL ; 
 scalar_t__ PARTOPEN ; 
 int _ov_open2 (TYPE_1__*) ; 

int ov_test_open(OggVorbis_File *vf){
  if(vf->ready_state!=PARTOPEN)return(OV_EINVAL);
  return _ov_open2(vf);
}