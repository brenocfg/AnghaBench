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
struct TYPE_7__ {TYPE_3__* backend_state; TYPE_1__* vi; } ;
typedef  TYPE_2__ vorbis_dsp_state ;
struct TYPE_8__ {int* window; } ;
typedef  TYPE_3__ private_state ;
struct TYPE_9__ {int halfrate_flag; } ;
typedef  TYPE_4__ codec_setup_info ;

/* Variables and functions */
 float const* _vorbis_window_get (int) ; 

const float *vorbis_window(vorbis_dsp_state *v,int W){
  vorbis_info *vi=v->vi;
  codec_setup_info *ci=vi->codec_setup;
  int hs=ci->halfrate_flag;
  private_state *b=v->backend_state;

  if(b->window[W]-1<0)return NULL;
  return _vorbis_window_get(b->window[W]-hs);
}