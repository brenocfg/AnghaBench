#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ogg_int64_t ;
struct TYPE_10__ {int (* tell_func ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* seek_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int serialno; } ;
struct TYPE_11__ {scalar_t__* dataoffsets; int offset; int end; int* serialnos; scalar_t__* pcmlengths; scalar_t__* offsets; int /*<<< orphan*/  datasource; TYPE_2__ callbacks; int /*<<< orphan*/  vi; TYPE_1__ os; } ;
typedef  TYPE_3__ OggVorbis_File ;

/* Variables and functions */
 int OV_EINVAL ; 
 int OV_EREAD ; 
 int /*<<< orphan*/  SEEK_END ; 
 scalar_t__ _bisect_forward_serialno (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int,int*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ _get_prev_page_serial (TYPE_3__*,int,int*,int,int*,scalar_t__*) ; 
 scalar_t__ _initial_pcmoffset (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ov_raw_seek (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _open_seekable2(OggVorbis_File *vf){
  ogg_int64_t dataoffset=vf->dataoffsets[0],end,endgran=-1;
  int endserial=vf->os.serialno;
  int serialno=vf->os.serialno;

  /* we're partially open and have a first link header state in
     storage in vf */

  /* fetch initial PCM offset */
  ogg_int64_t pcmoffset = _initial_pcmoffset(vf,vf->vi);

  /* we can seek, so set out learning all about this file */
  if(vf->callbacks.seek_func && vf->callbacks.tell_func){
    (vf->callbacks.seek_func)(vf->datasource,0,SEEK_END);
    vf->offset=vf->end=(vf->callbacks.tell_func)(vf->datasource);
  }else{
    vf->offset=vf->end=-1;
  }

  /* If seek_func is implemented, tell_func must also be implemented */
  if(vf->end==-1) return(OV_EINVAL);

  /* Get the offset of the last page of the physical bitstream, or, if
     we're lucky the last vorbis page of this link as most OggVorbis
     files will contain a single logical bitstream */
  end=_get_prev_page_serial(vf,vf->end,vf->serialnos+2,vf->serialnos[1],&endserial,&endgran);
  if(end<0)return(end);

  /* now determine bitstream structure recursively */
  if(_bisect_forward_serialno(vf,0,dataoffset,end,endgran,endserial,
                              vf->serialnos+2,vf->serialnos[1],0)<0)return(OV_EREAD);

  vf->offsets[0]=0;
  vf->serialnos[0]=serialno;
  vf->dataoffsets[0]=dataoffset;
  vf->pcmlengths[0]=pcmoffset;
  vf->pcmlengths[1]-=pcmoffset;
  if(vf->pcmlengths[1]<0)vf->pcmlengths[1]=0;

  return(ov_raw_seek(vf,dataoffset));
}