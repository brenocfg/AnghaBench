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
struct TYPE_5__ {TYPE_1__* vi; } ;
typedef  TYPE_2__ vorbis_dsp_state ;
typedef  int ogg_int64_t ;
struct TYPE_4__ {double rate; } ;

/* Variables and functions */

double vorbis_granule_time(vorbis_dsp_state *v,ogg_int64_t granulepos){
  if(granulepos == -1) return -1;

  /* We're not guaranteed a 64 bit unsigned type everywhere, so we
     have to put the unsigned granpo in a signed type. */
  if(granulepos>=0){
    return((double)granulepos/v->vi->rate);
  }else{
    ogg_int64_t granuleoff=0xffffffff;
    granuleoff<<=31;
    granuleoff|=0x7ffffffff;
    return(((double)granulepos+2+granuleoff+granuleoff)/v->vi->rate);
  }
}