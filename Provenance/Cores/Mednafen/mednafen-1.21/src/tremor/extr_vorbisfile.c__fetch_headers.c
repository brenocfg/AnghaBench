#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vorbis_info ;
typedef  int /*<<< orphan*/  vorbis_comment ;
typedef  int /*<<< orphan*/  ogg_uint32_t ;
typedef  int /*<<< orphan*/  ogg_page ;
typedef  int /*<<< orphan*/  ogg_packet ;
typedef  int ogg_int64_t ;
struct TYPE_8__ {scalar_t__ serialno; } ;
struct TYPE_7__ {scalar_t__ ready_state; TYPE_2__ os; } ;
typedef  TYPE_1__ OggVorbis_File ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNKSIZE ; 
 void* OPENED ; 
 int OV_EBADHEADER ; 
 int OV_ENOTVORBIS ; 
 int OV_EREAD ; 
 scalar_t__ STREAMSET ; 
 int /*<<< orphan*/  _add_serialno (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 
 scalar_t__ _get_next_page (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ _lookup_page_serialno (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _ogg_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ogg_page_bos (int /*<<< orphan*/ *) ; 
 scalar_t__ ogg_page_serialno (int /*<<< orphan*/ *) ; 
 int ogg_stream_packetout (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ogg_stream_pagein (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ogg_stream_reset_serialno (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  vorbis_comment_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vorbis_comment_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vorbis_info_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vorbis_info_init (int /*<<< orphan*/ *) ; 
 int vorbis_synthesis_headerin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vorbis_synthesis_idheader (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _fetch_headers(OggVorbis_File *vf,vorbis_info *vi,vorbis_comment *vc,
                          ogg_uint32_t **serialno_list, int *serialno_n,
                          ogg_page *og_ptr){
  ogg_page og;
  ogg_packet op;
  int i,ret;
  int allbos=0;

  if(!og_ptr){
    ogg_int64_t llret=_get_next_page(vf,&og,CHUNKSIZE);
    if(llret==OV_EREAD)return(OV_EREAD);
    if(llret<0)return(OV_ENOTVORBIS);
    og_ptr=&og;
  }

  vorbis_info_init(vi);
  vorbis_comment_init(vc);
  vf->ready_state=OPENED;

  /* extract the serialnos of all BOS pages + the first set of vorbis
     headers we see in the link */

  while(ogg_page_bos(og_ptr)){
    if(serialno_list){
      if(_lookup_page_serialno(og_ptr,*serialno_list,*serialno_n)){
        /* a dupe serialnumber in an initial header packet set == invalid stream */
        if(*serialno_list)_ogg_free(*serialno_list);
        *serialno_list=0;
        *serialno_n=0;
        ret=OV_EBADHEADER;
        goto bail_header;
      }

      _add_serialno(og_ptr,serialno_list,serialno_n);
    }

    if(vf->ready_state<STREAMSET){
      /* we don't have a vorbis stream in this link yet, so begin
         prospective stream setup. We need a stream to get packets */
      ogg_stream_reset_serialno(&vf->os,ogg_page_serialno(og_ptr));
      ogg_stream_pagein(&vf->os,og_ptr);

      if(ogg_stream_packetout(&vf->os,&op) > 0 &&
         vorbis_synthesis_idheader(&op)){
        /* vorbis header; continue setup */
        vf->ready_state=STREAMSET;
        if((ret=vorbis_synthesis_headerin(vi,vc,&op))){
          ret=OV_EBADHEADER;
          goto bail_header;
        }
      }
    }

    /* get next page */
    {
      ogg_int64_t llret=_get_next_page(vf,og_ptr,CHUNKSIZE);
      if(llret==OV_EREAD){
        ret=OV_EREAD;
        goto bail_header;
      }
      if(llret<0){
        ret=OV_ENOTVORBIS;
        goto bail_header;
      }

      /* if this page also belongs to our vorbis stream, submit it and break */
      if(vf->ready_state==STREAMSET &&
         vf->os.serialno == ogg_page_serialno(og_ptr)){
        ogg_stream_pagein(&vf->os,og_ptr);
        break;
      }
    }
  }

  if(vf->ready_state!=STREAMSET){
    ret = OV_ENOTVORBIS;
    goto bail_header;
  }

  while(1){

    i=0;
    while(i<2){ /* get a page loop */

      while(i<2){ /* get a packet loop */

        int result=ogg_stream_packetout(&vf->os,&op);
        if(result==0)break;
        if(result==-1){
          ret=OV_EBADHEADER;
          goto bail_header;
        }

        if((ret=vorbis_synthesis_headerin(vi,vc,&op)))
          goto bail_header;

        i++;
      }

      while(i<2){
        if(_get_next_page(vf,og_ptr,CHUNKSIZE)<0){
          ret=OV_EBADHEADER;
          goto bail_header;
        }

        /* if this page belongs to the correct stream, go parse it */
        if(vf->os.serialno == ogg_page_serialno(og_ptr)){
          ogg_stream_pagein(&vf->os,og_ptr);
          break;
        }

        /* if we never see the final vorbis headers before the link
           ends, abort */
        if(ogg_page_bos(og_ptr)){
          if(allbos){
            ret = OV_EBADHEADER;
            goto bail_header;
          }else
            allbos=1;
        }

        /* otherwise, keep looking */
      }
    }

    return 0;
  }

 bail_header:
  vorbis_info_clear(vi);
  vorbis_comment_clear(vc);
  vf->ready_state=OPENED;

  return ret;
}