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
typedef  int /*<<< orphan*/  vorbis_info ;
typedef  int /*<<< orphan*/  ogg_page ;
typedef  int /*<<< orphan*/  ogg_packet ;
typedef  scalar_t__ ogg_int64_t ;
struct TYPE_7__ {int serialno; } ;
struct TYPE_6__ {TYPE_2__ os; } ;
typedef  TYPE_1__ OggVorbis_File ;

/* Variables and functions */
 scalar_t__ _get_next_page (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ogg_page_bos (int /*<<< orphan*/ *) ; 
 int ogg_page_granulepos (int /*<<< orphan*/ *) ; 
 int ogg_page_serialno (int /*<<< orphan*/ *) ; 
 int ogg_stream_packetout (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ogg_stream_pagein (TYPE_2__*,int /*<<< orphan*/ *) ; 
 long vorbis_packet_blocksize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ogg_int64_t _initial_pcmoffset(OggVorbis_File *vf, vorbis_info *vi){
  ogg_page    og;
  ogg_int64_t accumulated=0;
  long        lastblock=-1;
  int         result;
  int         serialno = vf->os.serialno;

  while(1){
    ogg_packet op;
    if(_get_next_page(vf,&og,-1)<0)
      break; /* should not be possible unless the file is truncated/mangled */

    if(ogg_page_bos(&og)) break;
    if(ogg_page_serialno(&og)!=serialno) continue;

    /* count blocksizes of all frames in the page */
    ogg_stream_pagein(&vf->os,&og);
    while((result=ogg_stream_packetout(&vf->os,&op))){
      if(result>0){ /* ignore holes */
        long thisblock=vorbis_packet_blocksize(vi,&op);
        if(lastblock!=-1)
          accumulated+=(lastblock+thisblock)>>2;
        lastblock=thisblock;
      }
    }

    if(ogg_page_granulepos(&og)!=-1){
      /* pcm offset of last packet on the first audio page */
      accumulated= ogg_page_granulepos(&og)-accumulated;
      break;
    }
  }

  /* less than zero?  This is a stream with samples trimmed off
     the beginning, a normal occurrence; set the offset to zero */
  if(accumulated<0)accumulated=0;

  return accumulated;
}