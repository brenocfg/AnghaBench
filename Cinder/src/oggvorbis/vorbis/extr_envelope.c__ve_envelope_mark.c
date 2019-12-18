#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_5__* codec_setup; } ;
typedef  TYPE_1__ vorbis_info ;
struct TYPE_8__ {long centerW; size_t W; size_t lW; size_t nW; TYPE_1__* vi; scalar_t__ backend_state; } ;
typedef  TYPE_2__ vorbis_dsp_state ;
struct TYPE_9__ {TYPE_4__* ve; } ;
typedef  TYPE_3__ private_state ;
struct TYPE_10__ {long curmark; long searchstep; scalar_t__* mark; } ;
typedef  TYPE_4__ envelope_lookup ;
struct TYPE_11__ {int* blocksizes; } ;
typedef  TYPE_5__ codec_setup_info ;

/* Variables and functions */

int _ve_envelope_mark(vorbis_dsp_state *v){
  envelope_lookup *ve=((private_state *)(v->backend_state))->ve;
  vorbis_info *vi=v->vi;
  codec_setup_info *ci=vi->codec_setup;
  long centerW=v->centerW;
  long beginW=centerW-ci->blocksizes[v->W]/4;
  long endW=centerW+ci->blocksizes[v->W]/4;
  if(v->W){
    beginW-=ci->blocksizes[v->lW]/4;
    endW+=ci->blocksizes[v->nW]/4;
  }else{
    beginW-=ci->blocksizes[0]/4;
    endW+=ci->blocksizes[0]/4;
  }

  if(ve->curmark>=beginW && ve->curmark<endW)return(1);
  {
    long first=beginW/ve->searchstep;
    long last=endW/ve->searchstep;
    long i;
    for(i=first;i<last;i++)
      if(ve->mark[i])return(1);
  }
  return(0);
}