#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int channels; } ;
typedef  TYPE_1__ vorbis_info ;
typedef  int /*<<< orphan*/  vorbis_dsp_state ;
struct TYPE_7__ {int /*<<< orphan*/  vd; } ;
typedef  TYPE_2__ OggVorbis_File ;

/* Variables and functions */
 int OV_EOF ; 
 int _fetch_and_process_packet (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 
 int vorbis_synthesis_lapout (int /*<<< orphan*/ *,float***) ; 
 int vorbis_synthesis_pcmout (int /*<<< orphan*/ *,float***) ; 
 int /*<<< orphan*/  vorbis_synthesis_read (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void _ov_getlap(OggVorbis_File *vf,vorbis_info *vi,vorbis_dsp_state *vd,
                       float **lappcm,int lapsize){
  int lapcount=0,i;
  float **pcm;

  /* try first to decode the lapping data */
  while(lapcount<lapsize){
    int samples=vorbis_synthesis_pcmout(vd,&pcm);
    if(samples){
      if(samples>lapsize-lapcount)samples=lapsize-lapcount;
      for(i=0;i<vi->channels;i++)
        memcpy(lappcm[i]+lapcount,pcm[i],sizeof(**pcm)*samples);
      lapcount+=samples;
      vorbis_synthesis_read(vd,samples);
    }else{
    /* suck in another packet */
      int ret=_fetch_and_process_packet(vf,NULL,1,0); /* do *not* span */
      if(ret==OV_EOF)break;
    }
  }
  if(lapcount<lapsize){
    /* failed to get lapping data from normal decode; pry it from the
       postextrapolation buffering, or the second half of the MDCT
       from the last packet */
    int samples=vorbis_synthesis_lapout(&vf->vd,&pcm);
    if(samples==0){
      for(i=0;i<vi->channels;i++)
        memset(lappcm[i]+lapcount,0,sizeof(**pcm)*lapsize-lapcount);
      lapcount=lapsize;
    }else{
      if(samples>lapsize-lapcount)samples=lapsize-lapcount;
      for(i=0;i<vi->channels;i++)
        memcpy(lappcm[i]+lapcount,pcm[i],sizeof(**pcm)*samples);
      lapcount+=samples;
    }
  }
}