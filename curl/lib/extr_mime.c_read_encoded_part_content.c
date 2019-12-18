#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t bufbeg; size_t bufend; size_t buf; } ;
typedef  TYPE_2__ mime_encoder_state ;
struct TYPE_9__ {TYPE_1__* encoder; TYPE_2__ encstate; } ;
typedef  TYPE_3__ curl_mimepart ;
struct TYPE_7__ {size_t (* encodefunc ) (char*,size_t,int,TYPE_3__*) ;} ;

/* Variables and functions */
#define  CURL_READFUNC_ABORT 130 
#define  CURL_READFUNC_PAUSE 129 
 int FALSE ; 
#define  READ_ERROR 128 
 int TRUE ; 
 int /*<<< orphan*/  memmove (size_t,size_t,size_t) ; 
 size_t read_part_content (TYPE_3__*,size_t,int) ; 
 size_t stub1 (char*,size_t,int,TYPE_3__*) ; 

__attribute__((used)) static size_t read_encoded_part_content(curl_mimepart *part,
                                        char *buffer, size_t bufsize)
{
  mime_encoder_state *st = &part->encstate;
  size_t cursize = 0;
  size_t sz;
  bool ateof = FALSE;

  while(bufsize) {
    if(st->bufbeg < st->bufend || ateof) {
      /* Encode buffered data. */
      sz = part->encoder->encodefunc(buffer, bufsize, ateof, part);
      switch(sz) {
      case 0:
        if(ateof)
          return cursize;
        break;
      case CURL_READFUNC_ABORT:
      case CURL_READFUNC_PAUSE:
      case READ_ERROR:
        return cursize? cursize: sz;
      default:
        cursize += sz;
        buffer += sz;
        bufsize -= sz;
        continue;
      }
    }

    /* We need more data in input buffer. */
    if(st->bufbeg) {
      size_t len = st->bufend - st->bufbeg;

      if(len)
        memmove(st->buf, st->buf + st->bufbeg, len);
      st->bufbeg = 0;
      st->bufend = len;
    }
    if(st->bufend >= sizeof(st->buf))
      return cursize? cursize: READ_ERROR;    /* Buffer full. */
    sz = read_part_content(part, st->buf + st->bufend,
                           sizeof(st->buf) - st->bufend);
    switch(sz) {
    case 0:
      ateof = TRUE;
      break;
    case CURL_READFUNC_ABORT:
    case CURL_READFUNC_PAUSE:
    case READ_ERROR:
      return cursize? cursize: sz;
    default:
      st->bufend += sz;
      break;
    }
  }

  return cursize;
}