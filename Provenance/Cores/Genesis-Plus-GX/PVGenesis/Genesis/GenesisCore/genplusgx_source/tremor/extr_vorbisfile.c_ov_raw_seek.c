#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ogg_stream_state ;
struct TYPE_20__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ogg_page ;
struct TYPE_21__ {int granulepos; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ ogg_packet ;
typedef  scalar_t__ ogg_int64_t ;
struct TYPE_23__ {scalar_t__ codec_setup; } ;
struct TYPE_22__ {scalar_t__ ready_state; scalar_t__ end; int pcm_offset; scalar_t__ current_serialno; size_t current_link; scalar_t__* pcmlengths; int links; scalar_t__* serialnos; scalar_t__ samptrack; scalar_t__ bittrack; int /*<<< orphan*/ * os; TYPE_4__* vi; int /*<<< orphan*/  vd; int /*<<< orphan*/  seekable; } ;
typedef  TYPE_3__ OggVorbis_File ;

/* Variables and functions */
 scalar_t__ OPENED ; 
 int OV_EBADLINK ; 
 int OV_EINVAL ; 
 int OV_ENOSEEK ; 
 scalar_t__ STREAMSET ; 
 int /*<<< orphan*/  _decode_clear (TYPE_3__*) ; 
 scalar_t__ _get_next_page (TYPE_3__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  _seek_helper (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  ogg_packet_release (TYPE_2__*) ; 
 int /*<<< orphan*/  ogg_page_dup (TYPE_1__*,TYPE_1__*) ; 
 int ogg_page_eos (TYPE_1__*) ; 
 int /*<<< orphan*/  ogg_page_release (TYPE_1__*) ; 
 scalar_t__ ogg_page_serialno (TYPE_1__*) ; 
 int /*<<< orphan*/ * ogg_stream_create (scalar_t__) ; 
 int /*<<< orphan*/  ogg_stream_destroy (int /*<<< orphan*/ *) ; 
 int ogg_stream_packetout (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ogg_stream_pagein (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ogg_stream_reset_serialno (int /*<<< orphan*/ *,scalar_t__) ; 
 int ov_pcm_total (TYPE_3__*,int) ; 
 int vorbis_packet_blocksize (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  vorbis_synthesis_restart (int /*<<< orphan*/ *) ; 

int ov_raw_seek(OggVorbis_File *vf,ogg_int64_t pos){
  ogg_stream_state *work_os=NULL;
  ogg_page og={0,0,0,0};
  ogg_packet op={0,0,0,0,0,0};
  
  if(vf->ready_state<OPENED)return(OV_EINVAL);
  if(!vf->seekable)
    return(OV_ENOSEEK); /* don't dump machine if we can't seek */

  if(pos<0 || pos>vf->end)return(OV_EINVAL);

  /* don't yet clear out decoding machine (if it's initialized), in
     the case we're in the same link.  Restart the decode lapping, and
     let _fetch_and_process_packet deal with a potential bitstream
     boundary */
  vf->pcm_offset=-1;
  ogg_stream_reset_serialno(vf->os,
			    vf->current_serialno); /* must set serialno */
  vorbis_synthesis_restart(&vf->vd);
    
  _seek_helper(vf,pos);

  /* we need to make sure the pcm_offset is set, but we don't want to
     advance the raw cursor past good packets just to get to the first
     with a granulepos.  That's not equivalent behavior to beginning
     decoding as immediately after the seek position as possible.

     So, a hack.  We use two stream states; a local scratch state and
     the shared vf->os stream state.  We use the local state to
     scan, and the shared state as a buffer for later decode. 

     Unfortuantely, on the last page we still advance to last packet
     because the granulepos on the last page is not necessarily on a
     packet boundary, and we need to make sure the granpos is
     correct. 
  */

  {
    int lastblock=0;
    int accblock=0;
    int thisblock;
    int eosflag=0;

    work_os=ogg_stream_create(vf->current_serialno); /* get the memory ready */
    while(1){
      if(vf->ready_state>=STREAMSET){
	/* snarf/scan a packet if we can */
	int result=ogg_stream_packetout(work_os,&op);
      
	if(result>0){

	  if(vf->vi[vf->current_link].codec_setup){
	    thisblock=vorbis_packet_blocksize(vf->vi+vf->current_link,&op);
	    if(thisblock<0){
	      ogg_stream_packetout(vf->os,NULL);
	      thisblock=0;
	    }else{
	      
	      if(eosflag)
		ogg_stream_packetout(vf->os,NULL);
	      else
		if(lastblock)accblock+=(lastblock+thisblock)>>2;
	    }	    

	    if(op.granulepos!=-1){
	      int i,link=vf->current_link;
	      ogg_int64_t granulepos=op.granulepos-vf->pcmlengths[link*2];
	      if(granulepos<0)granulepos=0;
	      
	      for(i=0;i<link;i++)
		granulepos+=vf->pcmlengths[i*2+1];
	      vf->pcm_offset=granulepos-accblock;
	      break;
	    }
	    lastblock=thisblock;
	    continue;
	  }else
	    ogg_stream_packetout(vf->os,NULL);
	}
      }
      
      if(!lastblock){
	if(_get_next_page(vf,&og,-1)<0){
	  vf->pcm_offset=ov_pcm_total(vf,-1);
	  break;
	}
      }else{
	/* huh?  Bogus stream with packets but no granulepos */
	vf->pcm_offset=-1;
	break;
      }
      
      /* has our decoding just traversed a bitstream boundary? */
      if(vf->ready_state>=STREAMSET)
	if(vf->current_serialno!=ogg_page_serialno(&og)){
	  _decode_clear(vf); /* clear out stream state */
	  ogg_stream_destroy(work_os);
	}

      if(vf->ready_state<STREAMSET){
	int link;
	
	vf->current_serialno=ogg_page_serialno(&og);
	for(link=0;link<vf->links;link++)
	  if(vf->serialnos[link]==vf->current_serialno)break;
	if(link==vf->links)
	  goto seek_error; /* sign of a bogus stream.  error out,
			      leave machine uninitialized */
 
	vf->current_link=link;
	
	ogg_stream_reset_serialno(vf->os,vf->current_serialno);
	ogg_stream_reset_serialno(work_os,vf->current_serialno); 
	vf->ready_state=STREAMSET;
	
      }
    
      {
	ogg_page dup;
	ogg_page_dup(&dup,&og);
	eosflag=ogg_page_eos(&og);
	ogg_stream_pagein(vf->os,&og);
	ogg_stream_pagein(work_os,&dup);
      }
    }
  }

  ogg_packet_release(&op);
  ogg_page_release(&og);
  ogg_stream_destroy(work_os);
  vf->bittrack=0;
  vf->samptrack=0;
  return(0);

 seek_error:
  ogg_packet_release(&op);
  ogg_page_release(&og);

  /* dump the machine so we're in a known state */
  vf->pcm_offset=-1;
  ogg_stream_destroy(work_os);
  _decode_clear(vf);
  return OV_EBADLINK;
}