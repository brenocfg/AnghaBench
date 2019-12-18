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
struct TYPE_9__ {int comments; int* comment_lengths; void** user_comments; void* vendor; } ;
typedef  TYPE_1__ vorbis_comment ;
struct TYPE_10__ {int storage; } ;
typedef  TYPE_2__ oggpack_buffer ;

/* Variables and functions */
 int OV_EBADHEADER ; 
 void* _ogg_calloc (int,int) ; 
 int /*<<< orphan*/  _v_readstring (TYPE_2__*,void*,int) ; 
 int oggpack_bytes (TYPE_2__*) ; 
 int oggpack_read (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vorbis_comment_clear (TYPE_1__*) ; 

__attribute__((used)) static int _vorbis_unpack_comment(vorbis_comment *vc,oggpack_buffer *opb){
  int i;
  int vendorlen=oggpack_read(opb,32);
  if(vendorlen<0)goto err_out;
  if(vendorlen>opb->storage-8)goto err_out;
  vc->vendor=_ogg_calloc(vendorlen+1,1);
  _v_readstring(opb,vc->vendor,vendorlen);
  i=oggpack_read(opb,32);
  if(i<0)goto err_out;
  if(i>((opb->storage-oggpack_bytes(opb))>>2))goto err_out;
  vc->comments=i;
  vc->user_comments=_ogg_calloc(vc->comments+1,sizeof(*vc->user_comments));
  vc->comment_lengths=_ogg_calloc(vc->comments+1, sizeof(*vc->comment_lengths));

  for(i=0;i<vc->comments;i++){
    int len=oggpack_read(opb,32);
    if(len<0)goto err_out;
    if(len>opb->storage-oggpack_bytes(opb))goto err_out;
    vc->comment_lengths[i]=len;
    vc->user_comments[i]=_ogg_calloc(len+1,1);
    _v_readstring(opb,vc->user_comments[i],len);
  }
  if(oggpack_read(opb,1)!=1)goto err_out; /* EOP check */

  return(0);
 err_out:
  vorbis_comment_clear(vc);
  return(OV_EBADHEADER);
}