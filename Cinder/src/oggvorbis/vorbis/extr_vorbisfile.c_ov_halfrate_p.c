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
struct TYPE_3__ {int /*<<< orphan*/ * vi; } ;
typedef  TYPE_1__ OggVorbis_File ;

/* Variables and functions */
 int OV_EINVAL ; 
 int vorbis_synthesis_halfrate_p (int /*<<< orphan*/ *) ; 

int ov_halfrate_p(OggVorbis_File *vf){
  if(vf->vi==NULL)return OV_EINVAL;
  return vorbis_synthesis_halfrate_p(vf->vi);
}