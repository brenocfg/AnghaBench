#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ogg_int64_t ;
struct TYPE_4__ {scalar_t__ ready_state; int pcm_offset; int links; int /*<<< orphan*/ * vi; int /*<<< orphan*/  vb; int /*<<< orphan*/  vd; } ;
typedef  TYPE_1__ OggVorbis_File ;

/* Variables and functions */
 int OV_EINVAL ; 
 scalar_t__ STREAMSET ; 
 int /*<<< orphan*/  ov_pcm_seek (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vorbis_block_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vorbis_dsp_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ vorbis_synthesis_halfrate (int /*<<< orphan*/ *,int) ; 

int ov_halfrate(OggVorbis_File *vf,int flag){
  int i;
  if(vf->vi==NULL)return OV_EINVAL;
  if(vf->ready_state>STREAMSET){
    /* clear out stream state; dumping the decode machine is needed to
       reinit the MDCT lookups. */
    vorbis_dsp_clear(&vf->vd);
    vorbis_block_clear(&vf->vb);
    vf->ready_state=STREAMSET;
    if(vf->pcm_offset>=0){
      ogg_int64_t pos=vf->pcm_offset;
      vf->pcm_offset=-1; /* make sure the pos is dumped if unseekable */
      ov_pcm_seek(vf,pos);
    }
  }

  for(i=0;i<vf->links;i++){
    if(vorbis_synthesis_halfrate(vf->vi+i,flag)){
      if(flag) ov_halfrate(vf,0);
      return OV_EINVAL;
    }
  }
  return 0;
}