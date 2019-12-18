#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ogg_int32_t ;
struct TYPE_7__ {long channels; } ;
struct TYPE_6__ {scalar_t__ ready_state; long pcm_offset; int current_link; int /*<<< orphan*/  vd; } ;
typedef  TYPE_1__ OggVorbis_File ;

/* Variables and functions */
 short CLIP_TO_15 (int) ; 
 scalar_t__ INITSET ; 
 scalar_t__ OPENED ; 
 long OV_EINVAL ; 
 int OV_EOF ; 
 int _fetch_and_process_packet (TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 
 TYPE_3__* ov_info (TYPE_1__*,int) ; 
 long vorbis_synthesis_pcmout (int /*<<< orphan*/ *,int***) ; 
 int /*<<< orphan*/  vorbis_synthesis_read (int /*<<< orphan*/ *,long) ; 

long ov_read(OggVorbis_File *vf,char *buffer,int bytes_req,int *bitstream){
  int i,j;

  ogg_int32_t **pcm;
  long samples;

  if(vf->ready_state<OPENED)return(OV_EINVAL);

  while(1){
    if(vf->ready_state==INITSET){
      samples=vorbis_synthesis_pcmout(&vf->vd,&pcm);
      if(samples)break;
    }

    /* suck in another packet */
    {
      int ret=_fetch_and_process_packet(vf,NULL,1,1);
      if(ret==OV_EOF)
        return(0);
      if(ret<=0)
        return(ret);
    }

  }

  if(samples>0){

    /* yay! proceed to pack data into the byte buffer */

    long channels=ov_info(vf,-1)->channels;

    if(samples>(bytes_req/(2*channels)))
      samples=bytes_req/(2*channels);

    for(i=0;i<channels;i++) { /* It's faster in this order */
      ogg_int32_t *src=pcm[i];
      short *dest=((short *)buffer)+i;
      for(j=0;j<samples;j++) {
        *dest=CLIP_TO_15(src[j]>>9);
        dest+=channels;
      }
    }

    vorbis_synthesis_read(&vf->vd,samples);
    vf->pcm_offset+=samples;
    if(bitstream)*bitstream=vf->current_link;
    return(samples*2*channels);
  }else{
    return(samples);
  }
}