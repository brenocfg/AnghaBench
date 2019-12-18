#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ready_state; float bittrack; float samptrack; int /*<<< orphan*/  vb; int /*<<< orphan*/  vd; scalar_t__ vi; scalar_t__ current_link; scalar_t__ seekable; } ;
typedef  TYPE_1__ OggVorbis_File ;

/* Variables and functions */
 scalar_t__ INITSET ; 
 int OV_EBADLINK ; 
 int OV_EFAULT ; 
 scalar_t__ STREAMSET ; 
 int /*<<< orphan*/  vorbis_block_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vorbis_synthesis_init (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int _make_decode_ready(OggVorbis_File *vf){
  if(vf->ready_state>STREAMSET)return 0;
  if(vf->ready_state<STREAMSET)return OV_EFAULT;
  if(vf->seekable){
    if(vorbis_synthesis_init(&vf->vd,vf->vi+vf->current_link))
      return OV_EBADLINK;
  }else{
    if(vorbis_synthesis_init(&vf->vd,vf->vi))
      return OV_EBADLINK;
  }
  vorbis_block_init(&vf->vd,&vf->vb);
  vf->ready_state=INITSET;
  vf->bittrack=0.f;
  vf->samptrack=0.f;
  return 0;
}