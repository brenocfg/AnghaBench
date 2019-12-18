#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ curl_off_t ;
struct TYPE_3__ {size_t offset; } ;
struct TYPE_4__ {scalar_t__ datasize; TYPE_1__ state; } ;
typedef  TYPE_2__ curl_mimepart ;

/* Variables and functions */
 int CURL_SEEKFUNC_FAIL ; 
 int CURL_SEEKFUNC_OK ; 
#define  SEEK_CUR 129 
#define  SEEK_END 128 

__attribute__((used)) static int mime_mem_seek(void *instream, curl_off_t offset, int whence)
{
  curl_mimepart *part = (curl_mimepart *) instream;

  switch(whence) {
  case SEEK_CUR:
    offset += part->state.offset;
    break;
  case SEEK_END:
    offset += part->datasize;
    break;
  }

  if(offset < 0 || offset > part->datasize)
    return CURL_SEEKFUNC_FAIL;

  part->state.offset = (size_t) offset;
  return CURL_SEEKFUNC_OK;
}