#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int channels; TYPE_5__* codec_setup; } ;
typedef  TYPE_1__ vorbis_info ;
struct TYPE_9__ {int pcm_current; int pcm_returned; size_t lW; size_t W; int nW; int sequence; int granulepos; int centerW; float** pcm; int eofflag; int /*<<< orphan*/  res_bits; int /*<<< orphan*/  floor_bits; int /*<<< orphan*/  time_bits; int /*<<< orphan*/  glue_bits; TYPE_4__* backend_state; TYPE_1__* vi; } ;
typedef  TYPE_2__ vorbis_dsp_state ;
struct TYPE_10__ {size_t W; int sequence; float** pcm; int granulepos; scalar_t__ eofflag; scalar_t__ res_bits; scalar_t__ floor_bits; scalar_t__ time_bits; scalar_t__ glue_bits; } ;
typedef  TYPE_3__ vorbis_block ;
struct TYPE_11__ {int sample_count; scalar_t__* window; } ;
typedef  TYPE_4__ private_state ;
struct TYPE_12__ {int halfrate_flag; int* blocksizes; } ;
typedef  TYPE_5__ codec_setup_info ;

/* Variables and functions */
 int OV_EINVAL ; 
 float* _vorbis_window_get (scalar_t__) ; 

int vorbis_synthesis_blockin(vorbis_dsp_state *v,vorbis_block *vb){
  vorbis_info *vi=v->vi;
  codec_setup_info *ci=vi->codec_setup;
  private_state *b=v->backend_state;
  int hs=ci->halfrate_flag;
  int i,j;

  if(!vb)return(OV_EINVAL);
  if(v->pcm_current>v->pcm_returned  && v->pcm_returned!=-1)return(OV_EINVAL);

  v->lW=v->W;
  v->W=vb->W;
  v->nW=-1;

  if((v->sequence==-1)||
     (v->sequence+1 != vb->sequence)){
    v->granulepos=-1; /* out of sequence; lose count */
    b->sample_count=-1;
  }

  v->sequence=vb->sequence;

  if(vb->pcm){  /* no pcm to process if vorbis_synthesis_trackonly
                   was called on block */
    int n=ci->blocksizes[v->W]>>(hs+1);
    int n0=ci->blocksizes[0]>>(hs+1);
    int n1=ci->blocksizes[1]>>(hs+1);

    int thisCenter;
    int prevCenter;

    v->glue_bits+=vb->glue_bits;
    v->time_bits+=vb->time_bits;
    v->floor_bits+=vb->floor_bits;
    v->res_bits+=vb->res_bits;

    if(v->centerW){
      thisCenter=n1;
      prevCenter=0;
    }else{
      thisCenter=0;
      prevCenter=n1;
    }

    /* v->pcm is now used like a two-stage double buffer.  We don't want
       to have to constantly shift *or* adjust memory usage.  Don't
       accept a new block until the old is shifted out */

    for(j=0;j<vi->channels;j++){
      /* the overlap/add section */
      if(v->lW){
        if(v->W){
          /* large/large */
          const float *w=_vorbis_window_get(b->window[1]-hs);
          float *pcm=v->pcm[j]+prevCenter;
          float *p=vb->pcm[j];
          for(i=0;i<n1;i++)
            pcm[i]=pcm[i]*w[n1-i-1] + p[i]*w[i];
        }else{
          /* large/small */
          const float *w=_vorbis_window_get(b->window[0]-hs);
          float *pcm=v->pcm[j]+prevCenter+n1/2-n0/2;
          float *p=vb->pcm[j];
          for(i=0;i<n0;i++)
            pcm[i]=pcm[i]*w[n0-i-1] +p[i]*w[i];
        }
      }else{
        if(v->W){
          /* small/large */
          const float *w=_vorbis_window_get(b->window[0]-hs);
          float *pcm=v->pcm[j]+prevCenter;
          float *p=vb->pcm[j]+n1/2-n0/2;
          for(i=0;i<n0;i++)
            pcm[i]=pcm[i]*w[n0-i-1] +p[i]*w[i];
          for(;i<n1/2+n0/2;i++)
            pcm[i]=p[i];
        }else{
          /* small/small */
          const float *w=_vorbis_window_get(b->window[0]-hs);
          float *pcm=v->pcm[j]+prevCenter;
          float *p=vb->pcm[j];
          for(i=0;i<n0;i++)
            pcm[i]=pcm[i]*w[n0-i-1] +p[i]*w[i];
        }
      }

      /* the copy section */
      {
        float *pcm=v->pcm[j]+thisCenter;
        float *p=vb->pcm[j]+n;
        for(i=0;i<n;i++)
          pcm[i]=p[i];
      }
    }

    if(v->centerW)
      v->centerW=0;
    else
      v->centerW=n1;

    /* deal with initial packet state; we do this using the explicit
       pcm_returned==-1 flag otherwise we're sensitive to first block
       being short or long */

    if(v->pcm_returned==-1){
      v->pcm_returned=thisCenter;
      v->pcm_current=thisCenter;
    }else{
      v->pcm_returned=prevCenter;
      v->pcm_current=prevCenter+
        ((ci->blocksizes[v->lW]/4+
        ci->blocksizes[v->W]/4)>>hs);
    }

  }

  /* track the frame number... This is for convenience, but also
     making sure our last packet doesn't end with added padding.  If
     the last packet is partial, the number of samples we'll have to
     return will be past the vb->granulepos.

     This is not foolproof!  It will be confused if we begin
     decoding at the last page after a seek or hole.  In that case,
     we don't have a starting point to judge where the last frame
     is.  For this reason, vorbisfile will always try to make sure
     it reads the last two marked pages in proper sequence */

  if(b->sample_count==-1){
    b->sample_count=0;
  }else{
    b->sample_count+=ci->blocksizes[v->lW]/4+ci->blocksizes[v->W]/4;
  }

  if(v->granulepos==-1){
    if(vb->granulepos!=-1){ /* only set if we have a position to set to */

      v->granulepos=vb->granulepos;

      /* is this a short page? */
      if(b->sample_count>v->granulepos){
        /* corner case; if this is both the first and last audio page,
           then spec says the end is cut, not beginning */
       long extra=b->sample_count-vb->granulepos;

        /* we use ogg_int64_t for granule positions because a
           uint64 isn't universally available.  Unfortunately,
           that means granposes can be 'negative' and result in
           extra being negative */
        if(extra<0)
          extra=0;

        if(vb->eofflag){
          /* trim the end */
          /* no preceding granulepos; assume we started at zero (we'd
             have to in a short single-page stream) */
          /* granulepos could be -1 due to a seek, but that would result
             in a long count, not short count */

          /* Guard against corrupt/malicious frames that set EOP and
             a backdated granpos; don't rewind more samples than we
             actually have */
          if(extra > (v->pcm_current - v->pcm_returned)<<hs)
            extra = (v->pcm_current - v->pcm_returned)<<hs;

          v->pcm_current-=extra>>hs;
        }else{
          /* trim the beginning */
          v->pcm_returned+=extra>>hs;
          if(v->pcm_returned>v->pcm_current)
            v->pcm_returned=v->pcm_current;
        }

      }

    }
  }else{
    v->granulepos+=ci->blocksizes[v->lW]/4+ci->blocksizes[v->W]/4;
    if(vb->granulepos!=-1 && v->granulepos!=vb->granulepos){

      if(v->granulepos>vb->granulepos){
        long extra=v->granulepos-vb->granulepos;

        if(extra)
          if(vb->eofflag){
            /* partial last frame.  Strip the extra samples off */

            /* Guard against corrupt/malicious frames that set EOP and
               a backdated granpos; don't rewind more samples than we
               actually have */
            if(extra > (v->pcm_current - v->pcm_returned)<<hs)
              extra = (v->pcm_current - v->pcm_returned)<<hs;

            /* we use ogg_int64_t for granule positions because a
               uint64 isn't universally available.  Unfortunately,
               that means granposes can be 'negative' and result in
               extra being negative */
            if(extra<0)
              extra=0;

            v->pcm_current-=extra>>hs;
          } /* else {Shouldn't happen *unless* the bitstream is out of
               spec.  Either way, believe the bitstream } */
      } /* else {Shouldn't happen *unless* the bitstream is out of
           spec.  Either way, believe the bitstream } */
      v->granulepos=vb->granulepos;
    }
  }

  /* Update, cleanup */

  if(vb->eofflag)v->eofflag=1;
  return(0);

}