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
struct TYPE_4__ {scalar_t__ codec_setup; } ;
typedef  TYPE_1__ vorbis_info ;
struct TYPE_5__ {int* blocksizes; } ;
typedef  TYPE_2__ codec_setup_info ;

/* Variables and functions */

int vorbis_info_blocksize(vorbis_info *vi,int zo){
  codec_setup_info *ci = (codec_setup_info *)vi->codec_setup;
  return ci ? ci->blocksizes[zo] : -1;
}