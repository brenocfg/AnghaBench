#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* vendor; int comments; char** user_comments; int* comment_lengths; } ;
typedef  TYPE_1__ vorbis_comment ;
typedef  int /*<<< orphan*/  oggpack_buffer ;

/* Variables and functions */
 int OV_EBADHEADER ; 
 scalar_t__ _ogg_calloc (int,int) ; 
 int /*<<< orphan*/  _v_readstring (int /*<<< orphan*/ *,char*,int) ; 
 int oggpack_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vorbis_comment_clear (TYPE_1__*) ; 

__attribute__((used)) static int _vorbis_unpack_comment(vorbis_comment *vc,oggpack_buffer *opb){
  int i;
  int vendorlen=oggpack_read(opb,32);
  if(vendorlen<0)goto err_out;
  vc->vendor=(char *)_ogg_calloc(vendorlen+1,1);
  _v_readstring(opb,vc->vendor,vendorlen);
  vc->comments=oggpack_read(opb,32);
  if(vc->comments<0)goto err_out;
  vc->user_comments=(char **)_ogg_calloc(vc->comments+1,sizeof(*vc->user_comments));
  vc->comment_lengths=(int *)_ogg_calloc(vc->comments+1, sizeof(*vc->comment_lengths));
	    
  for(i=0;i<vc->comments;i++){
    int len=oggpack_read(opb,32);
    if(len<0)goto err_out;
	vc->comment_lengths[i]=len;
    vc->user_comments[i]=(char *)_ogg_calloc(len+1,1);
    _v_readstring(opb,vc->user_comments[i],len);
  }	  
  if(oggpack_read(opb,1)!=1)goto err_out; /* EOP check */

  return(0);
 err_out:
  vorbis_comment_clear(vc);
  return(OV_EBADHEADER);
}