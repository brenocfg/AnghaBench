#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int comments; char** user_comments; int* comment_lengths; } ;
typedef  TYPE_1__ vorbis_comment ;
typedef  int /*<<< orphan*/  oggpack_buffer ;

/* Variables and functions */
 char* ENCODE_VENDOR_STRING ; 
 int /*<<< orphan*/  _v_writestring (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  oggpack_write (int /*<<< orphan*/ *,int,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static int _vorbis_pack_comment(oggpack_buffer *opb,vorbis_comment *vc){
  int bytes = strlen(ENCODE_VENDOR_STRING);

  /* preamble */
  oggpack_write(opb,0x03,8);
  _v_writestring(opb,"vorbis", 6);

  /* vendor */
  oggpack_write(opb,bytes,32);
  _v_writestring(opb,ENCODE_VENDOR_STRING, bytes);

  /* comments */

  oggpack_write(opb,vc->comments,32);
  if(vc->comments){
    int i;
    for(i=0;i<vc->comments;i++){
      if(vc->user_comments[i]){
        oggpack_write(opb,vc->comment_lengths[i],32);
        _v_writestring(opb,vc->user_comments[i], vc->comment_lengths[i]);
      }else{
        oggpack_write(opb,0,32);
      }
    }
  }
  oggpack_write(opb,1,1);

  return(0);
}