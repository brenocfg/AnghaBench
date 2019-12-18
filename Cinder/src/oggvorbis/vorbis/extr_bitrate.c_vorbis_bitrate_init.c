#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {long rate; TYPE_2__* codec_setup; } ;
typedef  TYPE_1__ vorbis_info ;
struct TYPE_11__ {long reservoir_bits; int avg_rate; int min_rate; int max_rate; long reservoir_bias; } ;
struct TYPE_9__ {int* blocksizes; TYPE_4__ bi; } ;
typedef  TYPE_2__ codec_setup_info ;
struct TYPE_10__ {int short_per_long; int managed; int avgfloat; long minmax_reservoir; long avg_reservoir; void* max_bitsper; void* min_bitsper; void* avg_bitsper; } ;
typedef  TYPE_3__ bitrate_manager_state ;
typedef  TYPE_4__ bitrate_manager_info ;

/* Variables and functions */
 int PACKETBLOBS ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 void* rint (int) ; 

void vorbis_bitrate_init(vorbis_info *vi,bitrate_manager_state *bm){
  codec_setup_info *ci=vi->codec_setup;
  bitrate_manager_info *bi=&ci->bi;

  memset(bm,0,sizeof(*bm));

  if(bi && (bi->reservoir_bits>0)){
    long ratesamples=vi->rate;
    int  halfsamples=ci->blocksizes[0]>>1;

    bm->short_per_long=ci->blocksizes[1]/ci->blocksizes[0];
    bm->managed=1;

    bm->avg_bitsper= rint(1.*bi->avg_rate*halfsamples/ratesamples);
    bm->min_bitsper= rint(1.*bi->min_rate*halfsamples/ratesamples);
    bm->max_bitsper= rint(1.*bi->max_rate*halfsamples/ratesamples);

    bm->avgfloat=PACKETBLOBS/2;

    /* not a necessary fix, but one that leads to a more balanced
       typical initialization */
    {
      long desired_fill=bi->reservoir_bits*bi->reservoir_bias;
      bm->minmax_reservoir=desired_fill;
      bm->avg_reservoir=desired_fill;
    }

  }
}