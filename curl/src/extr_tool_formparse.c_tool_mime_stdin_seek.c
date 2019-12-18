#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ curpos; scalar_t__ origin; int /*<<< orphan*/  data; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ tool_mime ;
typedef  scalar_t__ curl_off_t ;

/* Variables and functions */
 int CURL_SEEKFUNC_CANTSEEK ; 
 int CURL_SEEKFUNC_OK ; 
#define  SEEK_CUR 129 
#define  SEEK_END 128 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ fseek (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 

int tool_mime_stdin_seek(void *instream, curl_off_t offset, int whence)
{
  tool_mime *sip = (tool_mime *) instream;

  switch(whence) {
  case SEEK_CUR:
    offset += sip->curpos;
    break;
  case SEEK_END:
    offset += sip->size;
    break;
  }
  if(offset < 0)
    return CURL_SEEKFUNC_CANTSEEK;
  if(!sip->data) {
    if(fseek(stdin, (long) (offset + sip->origin), SEEK_SET))
      return CURL_SEEKFUNC_CANTSEEK;
  }
  sip->curpos = offset;
  return CURL_SEEKFUNC_OK;
}