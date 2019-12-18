#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int rate; TYPE_6__* codec_setup; } ;
typedef  TYPE_1__ vorbis_info ;
struct TYPE_11__ {TYPE_1__* vi; TYPE_5__* backend_state; } ;
typedef  TYPE_2__ vorbis_dsp_state ;
struct TYPE_12__ {int /*<<< orphan*/ * packetblob; } ;
typedef  TYPE_3__ vorbis_block_internal ;
struct TYPE_13__ {int W; TYPE_2__* vd; TYPE_3__* internal; } ;
typedef  TYPE_4__ vorbis_block ;
struct TYPE_16__ {long min_bitsper; long short_per_long; long max_bitsper; long avg_bitsper; long avg_reservoir; long minmax_reservoir; int choice; scalar_t__ avgfloat; TYPE_4__* vb; int /*<<< orphan*/  managed; } ;
struct TYPE_14__ {TYPE_7__ bms; } ;
typedef  TYPE_5__ private_state ;
struct TYPE_17__ {long reservoir_bits; long reservoir_bias; int slew_damp; } ;
struct TYPE_15__ {int* blocksizes; TYPE_8__ bi; } ;
typedef  TYPE_6__ codec_setup_info ;
typedef  TYPE_7__ bitrate_manager_state ;
typedef  TYPE_8__ bitrate_manager_info ;

/* Variables and functions */
 int PACKETBLOBS ; 
 int oggpack_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oggpack_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oggpack_writetrunc (int /*<<< orphan*/ ,long) ; 
 int rint (scalar_t__) ; 

int vorbis_bitrate_addblock(vorbis_block *vb){
  vorbis_block_internal *vbi=vb->internal;
  vorbis_dsp_state      *vd=vb->vd;
  private_state         *b=vd->backend_state;
  bitrate_manager_state *bm=&b->bms;
  vorbis_info           *vi=vd->vi;
  codec_setup_info      *ci=vi->codec_setup;
  bitrate_manager_info  *bi=&ci->bi;

  int  choice=rint(bm->avgfloat);
  long this_bits=oggpack_bytes(vbi->packetblob[choice])*8;
  long min_target_bits=(vb->W?bm->min_bitsper*bm->short_per_long:bm->min_bitsper);
  long max_target_bits=(vb->W?bm->max_bitsper*bm->short_per_long:bm->max_bitsper);
  int  samples=ci->blocksizes[vb->W]>>1;
  long desired_fill=bi->reservoir_bits*bi->reservoir_bias;
  if(!bm->managed){
    /* not a bitrate managed stream, but for API simplicity, we'll
       buffer the packet to keep the code path clean */

    if(bm->vb)return(-1); /* one has been submitted without
                             being claimed */
    bm->vb=vb;
    return(0);
  }

  bm->vb=vb;

  /* look ahead for avg floater */
  if(bm->avg_bitsper>0){
    double slew=0.;
    long avg_target_bits=(vb->W?bm->avg_bitsper*bm->short_per_long:bm->avg_bitsper);
    double slewlimit= 15./bi->slew_damp;

    /* choosing a new floater:
       if we're over target, we slew down
       if we're under target, we slew up

       choose slew as follows: look through packetblobs of this frame
       and set slew as the first in the appropriate direction that
       gives us the slew we want.  This may mean no slew if delta is
       already favorable.

       Then limit slew to slew max */

    if(bm->avg_reservoir+(this_bits-avg_target_bits)>desired_fill){
      while(choice>0 && this_bits>avg_target_bits &&
            bm->avg_reservoir+(this_bits-avg_target_bits)>desired_fill){
        choice--;
        this_bits=oggpack_bytes(vbi->packetblob[choice])*8;
      }
    }else if(bm->avg_reservoir+(this_bits-avg_target_bits)<desired_fill){
      while(choice+1<PACKETBLOBS && this_bits<avg_target_bits &&
            bm->avg_reservoir+(this_bits-avg_target_bits)<desired_fill){
        choice++;
        this_bits=oggpack_bytes(vbi->packetblob[choice])*8;
      }
    }

    slew=rint(choice-bm->avgfloat)/samples*vi->rate;
    if(slew<-slewlimit)slew=-slewlimit;
    if(slew>slewlimit)slew=slewlimit;
    choice=rint(bm->avgfloat+= slew/vi->rate*samples);
    this_bits=oggpack_bytes(vbi->packetblob[choice])*8;
  }



  /* enforce min(if used) on the current floater (if used) */
  if(bm->min_bitsper>0){
    /* do we need to force the bitrate up? */
    if(this_bits<min_target_bits){
      while(bm->minmax_reservoir-(min_target_bits-this_bits)<0){
        choice++;
        if(choice>=PACKETBLOBS)break;
        this_bits=oggpack_bytes(vbi->packetblob[choice])*8;
      }
    }
  }

  /* enforce max (if used) on the current floater (if used) */
  if(bm->max_bitsper>0){
    /* do we need to force the bitrate down? */
    if(this_bits>max_target_bits){
      while(bm->minmax_reservoir+(this_bits-max_target_bits)>bi->reservoir_bits){
        choice--;
        if(choice<0)break;
        this_bits=oggpack_bytes(vbi->packetblob[choice])*8;
      }
    }
  }

  /* Choice of packetblobs now made based on floater, and min/max
     requirements. Now boundary check extreme choices */

  if(choice<0){
    /* choosing a smaller packetblob is insufficient to trim bitrate.
       frame will need to be truncated */
    long maxsize=(max_target_bits+(bi->reservoir_bits-bm->minmax_reservoir))/8;
    bm->choice=choice=0;

    if(oggpack_bytes(vbi->packetblob[choice])>maxsize){

      oggpack_writetrunc(vbi->packetblob[choice],maxsize*8);
      this_bits=oggpack_bytes(vbi->packetblob[choice])*8;
    }
  }else{
    long minsize=(min_target_bits-bm->minmax_reservoir+7)/8;
    if(choice>=PACKETBLOBS)
      choice=PACKETBLOBS-1;

    bm->choice=choice;

    /* prop up bitrate according to demand. pad this frame out with zeroes */
    minsize-=oggpack_bytes(vbi->packetblob[choice]);
    while(minsize-->0)oggpack_write(vbi->packetblob[choice],0,8);
    this_bits=oggpack_bytes(vbi->packetblob[choice])*8;

  }

  /* now we have the final packet and the final packet size.  Update statistics */
  /* min and max reservoir */
  if(bm->min_bitsper>0 || bm->max_bitsper>0){

    if(max_target_bits>0 && this_bits>max_target_bits){
      bm->minmax_reservoir+=(this_bits-max_target_bits);
    }else if(min_target_bits>0 && this_bits<min_target_bits){
      bm->minmax_reservoir+=(this_bits-min_target_bits);
    }else{
      /* inbetween; we want to take reservoir toward but not past desired_fill */
      if(bm->minmax_reservoir>desired_fill){
        if(max_target_bits>0){ /* logical bulletproofing against initialization state */
          bm->minmax_reservoir+=(this_bits-max_target_bits);
          if(bm->minmax_reservoir<desired_fill)bm->minmax_reservoir=desired_fill;
        }else{
          bm->minmax_reservoir=desired_fill;
        }
      }else{
        if(min_target_bits>0){ /* logical bulletproofing against initialization state */
          bm->minmax_reservoir+=(this_bits-min_target_bits);
          if(bm->minmax_reservoir>desired_fill)bm->minmax_reservoir=desired_fill;
        }else{
          bm->minmax_reservoir=desired_fill;
        }
      }
    }
  }

  /* avg reservoir */
  if(bm->avg_bitsper>0){
    long avg_target_bits=(vb->W?bm->avg_bitsper*bm->short_per_long:bm->avg_bitsper);
    bm->avg_reservoir+=this_bits-avg_target_bits;
  }

  return(0);
}