#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ogg_int64_t ;
struct TYPE_3__ {scalar_t__ ready_state; int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ OggVorbis_File ;

/* Variables and functions */
 scalar_t__ OPENED ; 
 int /*<<< orphan*/  OV_EINVAL ; 

ogg_int64_t ov_raw_tell(OggVorbis_File *vf){
  if(vf->ready_state<OPENED)return(OV_EINVAL);
  return(vf->offset);
}