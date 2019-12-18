#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int header_len; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ogg_page ;
struct TYPE_18__ {int granulepos; int bytes; int /*<<< orphan*/  e_o_s; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ ogg_packet ;
typedef  int ogg_int64_t ;
struct TYPE_19__ {scalar_t__ ready_state; int bittrack; int current_link; int pcm_offset; scalar_t__ current_serialno; int links; scalar_t__* serialnos; int /*<<< orphan*/  os; int /*<<< orphan*/  vc; int /*<<< orphan*/  vi; scalar_t__ seekable; scalar_t__* pcmlengths; int /*<<< orphan*/  vd; int /*<<< orphan*/  samptrack; int /*<<< orphan*/  vb; } ;
typedef  TYPE_3__ OggVorbis_File ;

/* Variables and functions */
 scalar_t__ INITSET ; 
 scalar_t__ OPENED ; 
 int OV_EBADLINK ; 
 int OV_EFAULT ; 
 int OV_EOF ; 
 int OV_HOLE ; 
 scalar_t__ STREAMSET ; 
 int /*<<< orphan*/  _decode_clear (TYPE_3__*) ; 
 int _fetch_headers (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,TYPE_1__*) ; 
 int _get_next_page (TYPE_3__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  _make_decode_ready (TYPE_3__*) ; 
 int /*<<< orphan*/  ogg_packet_release (TYPE_2__*) ; 
 int /*<<< orphan*/  ogg_page_release (TYPE_1__*) ; 
 scalar_t__ ogg_page_serialno (TYPE_1__*) ; 
 int ogg_stream_packetout (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ogg_stream_pagein (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ogg_stream_reset_serialno (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vorbis_comment_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vorbis_info_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vorbis_synthesis (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  vorbis_synthesis_blockin (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vorbis_synthesis_pcmout (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _fetch_and_process_packet(OggVorbis_File *vf,
				     int readp,
				     int spanp){
  ogg_page og={0,0,0,0};
  ogg_packet op={0,0,0,0,0,0};
  int ret=0;

  /* handle one packet.  Try to fetch it from current stream state */
  /* extract packets from page */
  while(1){
    
    /* process a packet if we can.  If the machine isn't loaded,
       neither is a page */
    if(vf->ready_state==INITSET){
      while(1) {
	int result=ogg_stream_packetout(vf->os,&op);
	ogg_int64_t granulepos;

	if(result<0){
	  ret=OV_HOLE; /* hole in the data. */
	  goto cleanup;
	}
	if(result>0){
	  /* got a packet.  process it */
	  granulepos=op.granulepos;
	  if(!vorbis_synthesis(&vf->vb,&op,1)){ /* lazy check for lazy
						      header handling.  The
						      header packets aren't
						      audio, so if/when we
						      submit them,
						      vorbis_synthesis will
						      reject them */

	    /* suck in the synthesis data and track bitrate */
	    {
	      int oldsamples=vorbis_synthesis_pcmout(&vf->vd,NULL);
	      /* for proper use of libvorbis within libvorbisfile,
                 oldsamples will always be zero. */
	      if(oldsamples){
		ret=OV_EFAULT;
		goto cleanup;
	      }

	      vorbis_synthesis_blockin(&vf->vd,&vf->vb);
	      vf->samptrack+=vorbis_synthesis_pcmout(&vf->vd,NULL)-oldsamples;
	      vf->bittrack+=op.bytes*8;
	    }
	  
	    /* update the pcm offset. */
	    if(granulepos!=-1 && !op.e_o_s){
	      int link=(vf->seekable?vf->current_link:0);
	      int i,samples;
	    
	      /* this packet has a pcm_offset on it (the last packet
	         completed on a page carries the offset) After processing
	         (above), we know the pcm position of the *last* sample
	         ready to be returned. Find the offset of the *first*

	         As an aside, this trick is inaccurate if we begin
	         reading anew right at the last page; the end-of-stream
	         granulepos declares the last frame in the stream, and the
	         last packet of the last page may be a partial frame.
	         So, we need a previous granulepos from an in-sequence page
	         to have a reference point.  Thus the !op.e_o_s clause
	         above */

	      if(vf->seekable && link>0)
		granulepos-=vf->pcmlengths[link*2];
	      if(granulepos<0)granulepos=0; /* actually, this
					       shouldn't be possible
					       here unless the stream
					       is very broken */

	      samples=vorbis_synthesis_pcmout(&vf->vd,NULL);
	    
	      granulepos-=samples;
	      for(i=0;i<link;i++)
	        granulepos+=vf->pcmlengths[i*2+1];
	      vf->pcm_offset=granulepos;
	    }
	    ret=1;
	    goto cleanup;
	  }
	}
	else 
	  break;
      }
    }

    if(vf->ready_state>=OPENED){
      int ret;
      if(!readp){
	ret=0;
	goto cleanup;
      }
      if((ret=_get_next_page(vf,&og,-1))<0){
	ret=OV_EOF; /* eof. leave unitialized */
	goto cleanup;
      }

	/* bitrate tracking; add the header's bytes here, the body bytes
	   are done by packet above */
      vf->bittrack+=og.header_len*8;
      
      /* has our decoding just traversed a bitstream boundary? */
      if(vf->ready_state==INITSET){
	if(vf->current_serialno!=ogg_page_serialno(&og)){
	  if(!spanp){
	    ret=OV_EOF;
	    goto cleanup;
	  }

	  _decode_clear(vf);
	  
	  if(!vf->seekable){
	    vorbis_info_clear(vf->vi);
	    vorbis_comment_clear(vf->vc);
	  }
	}
      }
    }

    /* Do we need to load a new machine before submitting the page? */
    /* This is different in the seekable and non-seekable cases.  

       In the seekable case, we already have all the header
       information loaded and cached; we just initialize the machine
       with it and continue on our merry way.

       In the non-seekable (streaming) case, we'll only be at a
       boundary if we just left the previous logical bitstream and
       we're now nominally at the header of the next bitstream
    */

    if(vf->ready_state!=INITSET){ 
      int link;

      if(vf->ready_state<STREAMSET){
	if(vf->seekable){
	  vf->current_serialno=ogg_page_serialno(&og);
	  
	  /* match the serialno to bitstream section.  We use this rather than
	     offset positions to avoid problems near logical bitstream
	     boundaries */
	  for(link=0;link<vf->links;link++)
	    if(vf->serialnos[link]==vf->current_serialno)break;
	  if(link==vf->links){
	    ret=OV_EBADLINK; /* sign of a bogus stream.  error out,
				leave machine uninitialized */
	    goto cleanup;
	  }
	  
	  vf->current_link=link;
	  
	  ogg_stream_reset_serialno(vf->os,vf->current_serialno);
	  vf->ready_state=STREAMSET;
	  
	}else{
	  /* we're streaming */
	  /* fetch the three header packets, build the info struct */
	  
	  int ret=_fetch_headers(vf,vf->vi,vf->vc,&vf->current_serialno,&og);
	  if(ret) goto cleanup;
	  vf->current_link++;
	  link=0;
	}
      }
      
      _make_decode_ready(vf);
    }
    ogg_stream_pagein(vf->os,&og);
  }
 cleanup:
  ogg_packet_release(&op);
  ogg_page_release(&og);
  return ret;
}