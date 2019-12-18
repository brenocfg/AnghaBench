#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int header_len; } ;
typedef  TYPE_1__ ogg_page ;
struct TYPE_21__ {int granulepos; int bytes; int /*<<< orphan*/  e_o_s; } ;
typedef  TYPE_2__ ogg_packet ;
typedef  int ogg_int64_t ;
struct TYPE_23__ {long serialno; } ;
struct TYPE_22__ {scalar_t__ ready_state; int samptrack; int bittrack; int current_link; int pcm_offset; long current_serialno; int links; long* serialnos; TYPE_5__ os; int /*<<< orphan*/  vc; int /*<<< orphan*/  vi; scalar_t__ seekable; scalar_t__* pcmlengths; int /*<<< orphan*/  vd; int /*<<< orphan*/  vb; } ;
typedef  TYPE_3__ OggVorbis_File ;

/* Variables and functions */
 scalar_t__ INITSET ; 
 scalar_t__ OPENED ; 
 int OV_EFAULT ; 
 int OV_EOF ; 
 int OV_HOLE ; 
 scalar_t__ STREAMSET ; 
 int /*<<< orphan*/  _decode_clear (TYPE_3__*) ; 
 int _fetch_headers (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int _get_next_page (TYPE_3__*,TYPE_1__*,int) ; 
 int _make_decode_ready (TYPE_3__*) ; 
 scalar_t__ ogg_page_bos (TYPE_1__*) ; 
 long ogg_page_serialno (TYPE_1__*) ; 
 int ogg_stream_packetout (TYPE_5__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ogg_stream_pagein (TYPE_5__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ogg_stream_reset_serialno (TYPE_5__*,long) ; 
 int /*<<< orphan*/  vorbis_comment_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vorbis_info_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vorbis_synthesis (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  vorbis_synthesis_blockin (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vorbis_synthesis_halfrate_p (int /*<<< orphan*/ ) ; 
 int vorbis_synthesis_pcmout (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _fetch_and_process_packet(OggVorbis_File *vf,
                                     ogg_packet *op_in,
                                     int readp,
                                     int spanp){
  ogg_page og;

  /* handle one packet.  Try to fetch it from current stream state */
  /* extract packets from page */
  while(1){

    if(vf->ready_state==STREAMSET){
      int ret=_make_decode_ready(vf);
      if(ret<0)return ret;
    }

    /* process a packet if we can. */

    if(vf->ready_state==INITSET){
      int hs=vorbis_synthesis_halfrate_p(vf->vi);

      while(1) {
              ogg_packet op;
              ogg_packet *op_ptr=(op_in?op_in:&op);
        int result=ogg_stream_packetout(&vf->os,op_ptr);
        ogg_int64_t granulepos;

        op_in=NULL;
        if(result==-1)return(OV_HOLE); /* hole in the data. */
        if(result>0){
          /* got a packet.  process it */
          granulepos=op_ptr->granulepos;
          if(!vorbis_synthesis(&vf->vb,op_ptr)){ /* lazy check for lazy
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
              if(oldsamples)return(OV_EFAULT);

              vorbis_synthesis_blockin(&vf->vd,&vf->vb);
              vf->samptrack+=(vorbis_synthesis_pcmout(&vf->vd,NULL)<<hs);
              vf->bittrack+=op_ptr->bytes*8;
            }

            /* update the pcm offset. */
            if(granulepos!=-1 && !op_ptr->e_o_s){
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
                 to have a reference point.  Thus the !op_ptr->e_o_s clause
                 above */

              if(vf->seekable && link>0)
                granulepos-=vf->pcmlengths[link*2];
              if(granulepos<0)granulepos=0; /* actually, this
                                               shouldn't be possible
                                               here unless the stream
                                               is very broken */

              samples=(vorbis_synthesis_pcmout(&vf->vd,NULL)<<hs);

              granulepos-=samples;
              for(i=0;i<link;i++)
                granulepos+=vf->pcmlengths[i*2+1];
              vf->pcm_offset=granulepos;
            }
            return(1);
          }
        }
        else
          break;
      }
    }

    if(vf->ready_state>=OPENED){
      ogg_int64_t ret;

      while(1){
        /* the loop is not strictly necessary, but there's no sense in
           doing the extra checks of the larger loop for the common
           case in a multiplexed bistream where the page is simply
           part of a different logical bitstream; keep reading until
           we get one with the correct serialno */

        if(!readp)return(0);
        if((ret=_get_next_page(vf,&og,-1))<0){
          return(OV_EOF); /* eof. leave unitialized */
        }

        /* bitrate tracking; add the header's bytes here, the body bytes
           are done by packet above */
        vf->bittrack+=og.header_len*8;

        if(vf->ready_state==INITSET){
          if(vf->current_serialno!=ogg_page_serialno(&og)){

            /* two possibilities:
               1) our decoding just traversed a bitstream boundary
               2) another stream is multiplexed into this logical section */

            if(ogg_page_bos(&og)){
              /* boundary case */
              if(!spanp)
                return(OV_EOF);

              _decode_clear(vf);

              if(!vf->seekable){
                vorbis_info_clear(vf->vi);
                vorbis_comment_clear(vf->vc);
              }
              break;

            }else
              continue; /* possibility #2 */
          }
        }

        break;
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
          long serialno = ogg_page_serialno(&og);

          /* match the serialno to bitstream section.  We use this rather than
             offset positions to avoid problems near logical bitstream
             boundaries */

          for(link=0;link<vf->links;link++)
            if(vf->serialnos[link]==serialno)break;

          if(link==vf->links) continue; /* not the desired Vorbis
                                           bitstream section; keep
                                           trying */

          vf->current_serialno=serialno;
          vf->current_link=link;

          ogg_stream_reset_serialno(&vf->os,vf->current_serialno);
          vf->ready_state=STREAMSET;

        }else{
          /* we're streaming */
          /* fetch the three header packets, build the info struct */

          int ret=_fetch_headers(vf,vf->vi,vf->vc,NULL,NULL,&og);
          if(ret)return(ret);
          vf->current_serialno=vf->os.serialno;
          vf->current_link++;
          link=0;
        }
      }
    }

    /* the buffered page is the data we want, and we're ready for it;
       add it to the stream state */
    ogg_stream_pagein(&vf->os,&og);

  }
}