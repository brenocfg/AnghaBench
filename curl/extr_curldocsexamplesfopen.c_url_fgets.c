#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  file; } ;
struct TYPE_7__ {int type; size_t buffer_pos; char* buffer; TYPE_1__ handle; } ;
typedef  TYPE_2__ URL_FILE ;

/* Variables and functions */
#define  CFTYPE_CURL 129 
#define  CFTYPE_FILE 128 
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  errno ; 
 char* fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_buffer (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  use_buffer (TYPE_2__*,size_t) ; 

char *url_fgets(char *ptr, size_t size, URL_FILE *file)
{
  size_t want = size - 1;/* always need to leave room for zero termination */
  size_t loop;

  switch(file->type) {
  case CFTYPE_FILE:
    ptr = fgets(ptr, (int)size, file->handle.file);
    break;

  case CFTYPE_CURL:
    fill_buffer(file, want);

    /* check if there's data in the buffer - if not fill either errored or
     * EOF */
    if(!file->buffer_pos)
      return NULL;

    /* ensure only available data is considered */
    if(file->buffer_pos < want)
      want = file->buffer_pos;

    /*buffer contains data */
    /* look for newline or eof */
    for(loop = 0; loop < want; loop++) {
      if(file->buffer[loop] == '\n') {
        want = loop + 1;/* include newline */
        break;
      }
    }

    /* xfer data to caller */
    memcpy(ptr, file->buffer, want);
    ptr[want] = 0;/* always null terminate */

    use_buffer(file, want);

    break;

  default: /* unknown or supported type - oh dear */
    ptr = NULL;
    errno = EBADF;
    break;
  }

  return ptr;/*success */
}