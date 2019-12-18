#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ogg_stream_state ;
typedef  int /*<<< orphan*/  ogg_page ;
struct TYPE_11__ {int granulepos; } ;
typedef  TYPE_1__ ogg_packet ;
typedef  scalar_t__ ogg_int64_t ;
struct TYPE_13__ {scalar_t__ codec_setup; } ;
struct TYPE_12__ {scalar_t__ ready_state; scalar_t__ end; scalar_t__* offsets; size_t current_link; int pcm_offset; long current_serialno; scalar_t__* pcmlengths; int links; long* serialnos; scalar_t__* dataoffsets; float bittrack; float samptrack; int /*<<< orphan*/  os; TYPE_3__* vi; int /*<<< orphan*/  vd; int /*<<< orphan*/  seekable; } ;
typedef  TYPE_2__ OggVorbis_File ;

/* Variables and functions */
 scalar_t__ OPENED ; 
 int OV_EBADLINK ; 
 int OV_EINVAL ; 
 int OV_ENOSEEK ; 
 scalar_t__ STREAMSET ; 
 int /*<<< orphan*/  _decode_clear (TYPE_2__*) ; 
 scalar_t__ _get_next_page (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int _seek_helper (TYPE_2__*,scalar_t__) ; 
 scalar_t__ ogg_page_bos (int /*<<< orphan*/ *) ; 
 int ogg_page_eos (int /*<<< orphan*/ *) ; 
 long ogg_page_serialno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ogg_stream_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ogg_stream_init (int /*<<< orphan*/ *,long) ; 
 int ogg_stream_packetout (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ogg_stream_pagein (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ogg_stream_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ogg_stream_reset_serialno (int /*<<< orphan*/ *,long) ; 
 scalar_t__ ov_pcm_total (TYPE_2__*,int) ; 
 int vorbis_packet_blocksize (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  vorbis_synthesis_restart (int /*<<< orphan*/ *) ; 

int ov_raw_seek(OggVorbis_File *vf,ogg_int64_t pos){
  ogg_stream_state work_os;
  int ret;

  if(vf->ready_state<OPENED)return(OV_EINVAL);
  if(!vf->seekable)
    return(OV_ENOSEEK); /* don't dump machine if we can't seek */

  if(pos<0 || pos>vf->end)return(OV_EINVAL);

  /* is the seek position outside our current link [if any]? */
  if(vf->ready_state>=STREAMSET){
    if(pos<vf->offsets[vf->current_link] || pos>=vf->offsets[vf->current_link+1])
      _decode_clear(vf); /* clear out stream state */
  }

  /* don't yet clear out decoding machine (if it's initialized), in
     the case we're in the same link.  Restart the decode lapping, and
     let _fetch_and_process_packet deal with a potential bitstream
     boundary */
  vf->pcm_offset=-1;
  ogg_stream_reset_serialno(&vf->os,
                            vf->current_serialno); /* must set serialno */
  vorbis_synthesis_restart(&vf->vd);

  ret=_seek_helper(vf,pos);
  if(ret)goto seek_error;

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
    ogg_page og;
    ogg_packet op;
    int lastblock=0;
    int accblock=0;
    int thisblock=0;
    int lastflag=0;
    int firstflag=0;
    ogg_int64_t pagepos=-1;

    ogg_stream_init(&work_os,vf->current_serialno); /* get the memory ready */
    ogg_stream_reset(&work_os); /* eliminate the spurious OV_HOLE
                                   return from not necessarily
                                   starting from the beginning */

    while(1){
      if(vf->ready_state>=STREAMSET){
        /* snarf/scan a packet if we can */
        int result=ogg_stream_packetout(&work_os,&op);

        if(result>0){

          if(vf->vi[vf->current_link].codec_setup){
            thisblock=vorbis_packet_blocksize(vf->vi+vf->current_link,&op);
            if(thisblock<0){
              ogg_stream_packetout(&vf->os,NULL);
              thisblock=0;
            }else{

              /* We can't get a guaranteed correct pcm position out of the
                 last page in a stream because it might have a 'short'
                 granpos, which can only be detected in the presence of a
                 preceding page.  However, if the last page is also the first
                 page, the granpos rules of a first page take precedence.  Not
                 only that, but for first==last, the EOS page must be treated
                 as if its a normal first page for the stream to open/play. */
              if(lastflag && !firstflag)
                ogg_stream_packetout(&vf->os,NULL);
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
              if(vf->pcm_offset<0)vf->pcm_offset=0;
              break;
            }
            lastblock=thisblock;
            continue;
          }else
            ogg_stream_packetout(&vf->os,NULL);
        }
      }

      if(!lastblock){
        pagepos=_get_next_page(vf,&og,-1);
        if(pagepos<0){
          vf->pcm_offset=ov_pcm_total(vf,-1);
          break;
        }
      }else{
        /* huh?  Bogus stream with packets but no granulepos */
        vf->pcm_offset=-1;
        break;
      }

      /* has our decoding just traversed a bitstream boundary? */
      if(vf->ready_state>=STREAMSET){
        if(vf->current_serialno!=ogg_page_serialno(&og)){

          /* two possibilities:
             1) our decoding just traversed a bitstream boundary
             2) another stream is multiplexed into this logical section? */

          if(ogg_page_bos(&og)){
            /* we traversed */
            _decode_clear(vf); /* clear out stream state */
            ogg_stream_clear(&work_os);
          } /* else, do nothing; next loop will scoop another page */
        }
      }

      if(vf->ready_state<STREAMSET){
        int link;
        long serialno = ogg_page_serialno(&og);

        for(link=0;link<vf->links;link++)
          if(vf->serialnos[link]==serialno)break;

        if(link==vf->links) continue; /* not the desired Vorbis
                                         bitstream section; keep
                                         trying */
        vf->current_link=link;
        vf->current_serialno=serialno;
        ogg_stream_reset_serialno(&vf->os,serialno);
        ogg_stream_reset_serialno(&work_os,serialno);
        vf->ready_state=STREAMSET;
        firstflag=(pagepos<=vf->dataoffsets[link]);
      }

      ogg_stream_pagein(&vf->os,&og);
      ogg_stream_pagein(&work_os,&og);
      lastflag=ogg_page_eos(&og);

    }
  }

  ogg_stream_clear(&work_os);
  vf->bittrack=0.f;
  vf->samptrack=0.f;
  return(0);

 seek_error:
  /* dump the machine so we're in a known state */
  vf->pcm_offset=-1;
  ogg_stream_clear(&work_os);
  _decode_clear(vf);
  return OV_EBADLINK;
}