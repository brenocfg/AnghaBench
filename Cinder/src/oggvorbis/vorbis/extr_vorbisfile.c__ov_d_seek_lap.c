#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int channels; } ;
typedef  TYPE_1__ vorbis_info ;
struct TYPE_15__ {scalar_t__ ready_state; int /*<<< orphan*/  vd; } ;
typedef  TYPE_2__ OggVorbis_File ;

/* Variables and functions */
 scalar_t__ OPENED ; 
 int OV_EINVAL ; 
 int /*<<< orphan*/  _ov_getlap (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,float**,int) ; 
 int _ov_initprime (TYPE_2__*) ; 
 int _ov_initset (TYPE_2__*) ; 
 int /*<<< orphan*/  _ov_splice (float**,float**,int,int,int,int,float const*,float const*) ; 
 void* alloca (int) ; 
 int ov_halfrate_p (TYPE_2__*) ; 
 TYPE_1__* ov_info (TYPE_2__*,int) ; 
 int vorbis_info_blocksize (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vorbis_synthesis_lapout (int /*<<< orphan*/ *,float***) ; 
 float* vorbis_window (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _ov_d_seek_lap(OggVorbis_File *vf,double pos,
                           int (*localseek)(OggVorbis_File *,double)){
  vorbis_info *vi;
  float **lappcm;
  float **pcm;
  const float *w1,*w2;
  int n1,n2,ch1,ch2,hs;
  int i,ret;

  if(vf->ready_state<OPENED)return(OV_EINVAL);
  ret=_ov_initset(vf);
  if(ret)return(ret);
  vi=ov_info(vf,-1);
  hs=ov_halfrate_p(vf);

  ch1=vi->channels;
  n1=vorbis_info_blocksize(vi,0)>>(1+hs);
  w1=vorbis_window(&vf->vd,0);  /* window arrays from libvorbis are
                                   persistent; even if the decode state
                                   from this link gets dumped, this
                                   window array continues to exist */

  lappcm=alloca(sizeof(*lappcm)*ch1);
  for(i=0;i<ch1;i++)
    lappcm[i]=alloca(sizeof(**lappcm)*n1);
  _ov_getlap(vf,vi,&vf->vd,lappcm,n1);

  /* have lapping data; seek and prime the buffer */
  ret=localseek(vf,pos);
  if(ret)return ret;
  ret=_ov_initprime(vf);
  if(ret)return(ret);

 /* Guard against cross-link changes; they're perfectly legal */
  vi=ov_info(vf,-1);
  ch2=vi->channels;
  n2=vorbis_info_blocksize(vi,0)>>(1+hs);
  w2=vorbis_window(&vf->vd,0);

  /* consolidate and expose the buffer. */
  vorbis_synthesis_lapout(&vf->vd,&pcm);

  /* splice */
  _ov_splice(pcm,lappcm,n1,n2,ch1,ch2,w1,w2);

  /* done */
  return(0);
}