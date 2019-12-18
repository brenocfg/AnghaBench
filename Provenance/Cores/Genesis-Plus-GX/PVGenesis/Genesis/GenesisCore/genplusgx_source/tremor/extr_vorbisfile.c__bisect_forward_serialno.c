#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ogg_uint32_t ;
struct TYPE_9__ {scalar_t__ header_len; scalar_t__ body_len; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ogg_page ;
typedef  scalar_t__ ogg_int64_t ;
struct TYPE_10__ {long links; scalar_t__ offset; scalar_t__* serialnos; scalar_t__* offsets; } ;
typedef  TYPE_2__ OggVorbis_File ;

/* Variables and functions */
 scalar_t__ CHUNKSIZE ; 
 scalar_t__ OV_EREAD ; 
 scalar_t__ _get_next_page (TYPE_2__*,TYPE_1__*,int) ; 
 void* _ogg_malloc (int) ; 
 int /*<<< orphan*/  _seek_helper (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  ogg_page_release (TYPE_1__*) ; 
 scalar_t__ ogg_page_serialno (TYPE_1__*) ; 

__attribute__((used)) static int _bisect_forward_serialno(OggVorbis_File *vf,
				    ogg_int64_t begin,
				    ogg_int64_t searched,
				    ogg_int64_t end,
				    ogg_uint32_t currentno,
				    long m){
  ogg_int64_t endsearched=end;
  ogg_int64_t next=end;
  ogg_page og={0,0,0,0};
  ogg_int64_t ret;
  
  /* the below guards against garbage seperating the last and
     first pages of two links. */
  while(searched<endsearched){
    ogg_int64_t bisect;
    
    if(endsearched-searched<CHUNKSIZE){
      bisect=searched;
    }else{
      bisect=(searched+endsearched)/2;
    }
    
    _seek_helper(vf,bisect);
    ret=_get_next_page(vf,&og,-1);
    if(ret==OV_EREAD)return(OV_EREAD);
    if(ret<0 || ogg_page_serialno(&og)!=currentno){
      endsearched=bisect;
      if(ret>=0)next=ret;
    }else{
      searched=ret+og.header_len+og.body_len;
    }
    ogg_page_release(&og);
  }

  _seek_helper(vf,next);
  ret=_get_next_page(vf,&og,-1);
  if(ret==OV_EREAD)return(OV_EREAD);
  
  if(searched>=end || ret<0){
    ogg_page_release(&og);
    vf->links=m+1;
    vf->offsets=_ogg_malloc((vf->links+1)*sizeof(*vf->offsets));
    vf->serialnos=_ogg_malloc(vf->links*sizeof(*vf->serialnos));
    vf->offsets[m+1]=searched;
  }else{
    ret=_bisect_forward_serialno(vf,next,vf->offset,
				 end,ogg_page_serialno(&og),m+1);
    ogg_page_release(&og);
    if(ret==OV_EREAD)return(OV_EREAD);
  }
  
  vf->offsets[m]=begin;
  vf->serialnos[m]=currentno;
  return(0);
}