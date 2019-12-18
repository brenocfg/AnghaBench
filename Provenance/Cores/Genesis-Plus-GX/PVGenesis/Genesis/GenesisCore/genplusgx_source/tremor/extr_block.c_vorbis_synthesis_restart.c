#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_4__* codec_setup; } ;
typedef  TYPE_1__ vorbis_info ;
struct TYPE_7__ {int centerW; int pcm_current; int pcm_returned; int granulepos; int sequence; scalar_t__ backend_state; TYPE_1__* vi; } ;
typedef  TYPE_2__ vorbis_dsp_state ;
struct TYPE_8__ {int sample_count; } ;
typedef  TYPE_3__ private_state ;
struct TYPE_9__ {int* blocksizes; } ;
typedef  TYPE_4__ codec_setup_info ;

/* Variables and functions */

int vorbis_synthesis_restart(vorbis_dsp_state *v){
  vorbis_info *vi=v->vi;
  codec_setup_info *ci;

  if(!v->backend_state)return -1;
  if(!vi)return -1;
  ci=vi->codec_setup;
  if(!ci)return -1;

  v->centerW=ci->blocksizes[1]/2;
  v->pcm_current=v->centerW;
  
  v->pcm_returned=-1;
  v->granulepos=-1;
  v->sequence=-1;
  ((private_state *)(v->backend_state))->sample_count=-1;

  return(0);
}