#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t bufbeg; size_t bufend; int* buf; scalar_t__ pos; } ;
typedef  TYPE_1__ mime_encoder_state ;
struct TYPE_6__ {TYPE_1__ encstate; } ;
typedef  TYPE_2__ curl_mimepart ;

/* Variables and functions */
 scalar_t__ MAX_ENCODED_LINE_LENGTH ; 
#define  QP_CR 130 
#define  QP_OK 129 
#define  QP_SP 128 
 char* aschex ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int* qp_class ; 
 int qp_lookahead_eol (TYPE_1__*,int,size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static size_t encoder_qp_read(char *buffer, size_t size, bool ateof,
                              curl_mimepart *part)
{
  mime_encoder_state *st = &part->encstate;
  char *ptr = buffer;
  size_t cursize = 0;
  int softlinebreak;
  char buf[4];

  /* On all platforms, input is supposed to be ASCII compatible: for this
     reason, we use hexadecimal ASCII codes in this function rather than
     character constants that can be interpreted as non-ascii on some
     platforms. Preserve ASCII encoding on output too. */
  while(st->bufbeg < st->bufend) {
    size_t len = 1;
    size_t consumed = 1;
    int i = st->buf[st->bufbeg];
    buf[0] = (char) i;
    buf[1] = aschex[(i >> 4) & 0xF];
    buf[2] = aschex[i & 0xF];

    switch(qp_class[st->buf[st->bufbeg] & 0xFF]) {
    case QP_OK:          /* Not a special character. */
      break;
    case QP_SP:          /* Space or tab. */
      /* Spacing must be escaped if followed by CRLF. */
      switch(qp_lookahead_eol(st, ateof, 1)) {
      case -1:          /* More input data needed. */
        return cursize;
      case 0:           /* No encoding needed. */
        break;
      default:          /* CRLF after space or tab. */
        buf[0] = '\x3D';    /* '=' */
        len = 3;
        break;
      }
      break;
    case QP_CR:         /* Carriage return. */
      /* If followed by a line-feed, output the CRLF pair.
         Else escape it. */
      switch(qp_lookahead_eol(st, ateof, 0)) {
      case -1:          /* Need more data. */
        return cursize;
      case 1:           /* CRLF found. */
        buf[len++] = '\x0A';    /* Append '\n'. */
        consumed = 2;
        break;
      default:          /* Not followed by LF: escape. */
        buf[0] = '\x3D';    /* '=' */
        len = 3;
        break;
      }
      break;
    default:            /* Character must be escaped. */
      buf[0] = '\x3D';    /* '=' */
      len = 3;
      break;
    }

    /* Be sure the encoded character fits within maximum line length. */
    if(buf[len - 1] != '\x0A') {    /* '\n' */
      softlinebreak = st->pos + len > MAX_ENCODED_LINE_LENGTH;
      if(!softlinebreak && st->pos + len == MAX_ENCODED_LINE_LENGTH) {
        /* We may use the current line only if end of data or followed by
           a CRLF. */
        switch(qp_lookahead_eol(st, ateof, consumed)) {
        case -1:        /* Need more data. */
          return cursize;
          break;
        case 0:         /* Not followed by a CRLF. */
          softlinebreak = 1;
          break;
        }
      }
      if(softlinebreak) {
        strcpy(buf, "\x3D\x0D\x0A");    /* "=\r\n" */
        len = 3;
        consumed = 0;
      }
    }

    /* If the output buffer would overflow, do not store. */
    if(len > size)
      break;

    /* Append to output buffer. */
    memcpy(ptr, buf, len);
    cursize += len;
    ptr += len;
    size -= len;
    st->pos += len;
    if(buf[len - 1] == '\x0A')    /* '\n' */
      st->pos = 0;
    st->bufbeg += consumed;
  }

  return cursize;
}