#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* nextpart; } ;
typedef  TYPE_1__ curl_mimepart ;
struct TYPE_9__ {int state; int offset; TYPE_1__* ptr; } ;
struct TYPE_8__ {char* boundary; scalar_t__ easy; TYPE_4__ state; TYPE_1__* firstpart; } ;
typedef  TYPE_2__ curl_mime ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
#define  CURL_READFUNC_ABORT 136 
#define  CURL_READFUNC_PAUSE 135 
 scalar_t__ Curl_convert_to_network (scalar_t__,char*,int) ; 
#define  MIMESTATE_BEGIN 134 
#define  MIMESTATE_BODY 133 
#define  MIMESTATE_BOUNDARY1 132 
#define  MIMESTATE_BOUNDARY2 131 
#define  MIMESTATE_CONTENT 130 
#define  MIMESTATE_END 129 
#define  READ_ERROR 128 
 int /*<<< orphan*/  mimesetstate (TYPE_4__*,int const,TYPE_1__*) ; 
 size_t readback_bytes (TYPE_4__*,char*,size_t,char*,int,char*) ; 
 size_t readback_part (TYPE_1__*,char*,size_t) ; 
 int strlen (char*) ; 

__attribute__((used)) static size_t mime_subparts_read(char *buffer, size_t size, size_t nitems,
                                 void *instream)
{
  curl_mime *mime = (curl_mime *) instream;
  size_t cursize = 0;
#ifdef CURL_DOES_CONVERSIONS
  char *convbuf = buffer;
#endif

  (void) size;   /* Always 1. */

  while(nitems) {
    size_t sz = 0;
    curl_mimepart *part = mime->state.ptr;
    switch(mime->state.state) {
    case MIMESTATE_BEGIN:
    case MIMESTATE_BODY:
#ifdef CURL_DOES_CONVERSIONS
      convbuf = buffer;
#endif
      mimesetstate(&mime->state, MIMESTATE_BOUNDARY1, mime->firstpart);
      /* The first boundary always follows the header termination empty line,
         so is always preceded by a CRLK. We can then spare 2 characters
         by skipping the leading CRLF in boundary. */
      mime->state.offset += 2;
      break;
    case MIMESTATE_BOUNDARY1:
      sz = readback_bytes(&mime->state, buffer, nitems, "\r\n--", 4, "");
      if(!sz)
        mimesetstate(&mime->state, MIMESTATE_BOUNDARY2, part);
      break;
    case MIMESTATE_BOUNDARY2:
      sz = readback_bytes(&mime->state, buffer, nitems, mime->boundary,
                          strlen(mime->boundary), part? "\r\n": "--\r\n");
      if(!sz) {
#ifdef CURL_DOES_CONVERSIONS
        if(mime->easy && convbuf < buffer) {
          CURLcode result = Curl_convert_to_network(mime->easy, convbuf,
                                                    buffer - convbuf);
          if(result)
            return READ_ERROR;
          convbuf = buffer;
        }
#endif
        mimesetstate(&mime->state, MIMESTATE_CONTENT, part);
      }
      break;
    case MIMESTATE_CONTENT:
      if(!part) {
        mimesetstate(&mime->state, MIMESTATE_END, NULL);
        break;
      }
      sz = readback_part(part, buffer, nitems);
      switch(sz) {
      case CURL_READFUNC_ABORT:
      case CURL_READFUNC_PAUSE:
      case READ_ERROR:
        return cursize? cursize: sz;
      case 0:
#ifdef CURL_DOES_CONVERSIONS
        convbuf = buffer;
#endif
        mimesetstate(&mime->state, MIMESTATE_BOUNDARY1, part->nextpart);
        break;
      }
      break;
    case MIMESTATE_END:
      return cursize;
    default:
      break;    /* other values not used in mime state. */
    }

    /* Bump buffer and counters according to read size. */
    cursize += sz;
    buffer += sz;
    nitems -= sz;
  }

#ifdef CURL_DOES_CONVERSIONS
      if(mime->easy && convbuf < buffer &&
         mime->state.state <= MIMESTATE_CONTENT) {
        CURLcode result = Curl_convert_to_network(mime->easy, convbuf,
                                                  buffer - convbuf);
        if(result)
          return READ_ERROR;
      }
#endif

  return cursize;
}