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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_3__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* mb_to_wc_fallback ) (char const*,size_t,int /*<<< orphan*/ ,struct mb_to_wc_fallback_locals*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ fallbacks; scalar_t__ discard_ilseq; } ;
struct wchar_conv_struct {TYPE_2__ parent; int /*<<< orphan*/  state; } ;
struct mb_to_wc_fallback_locals {char* l_outbuf; size_t l_outbytesleft; scalar_t__ l_errno; } ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 int BUF_SIZE ; 
 scalar_t__ E2BIG ; 
 scalar_t__ EILSEQ ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  mb_to_wc_write_replacement ; 
 size_t mbrtowc (int /*<<< orphan*/ *,char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (char const*,size_t,int /*<<< orphan*/ ,struct mb_to_wc_fallback_locals*,int /*<<< orphan*/ ) ; 
 size_t unicode_loop_convert (TYPE_2__*,char const**,size_t*,char**,size_t*) ; 

__attribute__((used)) static size_t wchar_to_loop_convert (iconv_t icd,
                                     const char* * inbuf, size_t *inbytesleft,
                                     char* * outbuf, size_t *outbytesleft)
{
  struct wchar_conv_struct * wcd = (struct wchar_conv_struct *) icd;
  size_t result = 0;
  while (*inbytesleft > 0) {
    size_t incount;
    for (incount = 1; ; ) {
      /* Here incount <= *inbytesleft. */
      char buf[BUF_SIZE];
      const char* inptr = *inbuf;
      size_t inleft = incount;
      char* bufptr = buf;
      size_t bufleft = BUF_SIZE;
      size_t res = unicode_loop_convert(&wcd->parent,
                                        &inptr,&inleft,
                                        &bufptr,&bufleft);
      if (res == (size_t)(-1)) {
        if (errno == EILSEQ)
          /* Invalid input. */
          return -1;
        else if (errno == EINVAL) {
          /* Incomplete input. Next try with one more input byte. */
        } else
          /* E2BIG shouldn't occur. */
          abort();
      } else {
        /* Successful conversion. */
        size_t bufcount = bufptr-buf; /* = BUF_SIZE-bufleft */
        mbstate_t state = wcd->state;
        wchar_t wc;
        res = mbrtowc(&wc,buf,bufcount,&state);
        if (res == (size_t)(-2)) {
          /* Next try with one more input byte. */
        } else {
          if (res == (size_t)(-1)) {
            /* Invalid input. */
            if (wcd->parent.discard_ilseq) {
            }
            #ifndef LIBICONV_PLUG
            else if (wcd->parent.fallbacks.mb_to_wc_fallback != NULL) {
              /* Drop the contents of buf[] accumulated so far, and instead
                 pass all queued chars to the fallback handler. */
              struct mb_to_wc_fallback_locals locals;
              locals.l_outbuf = *outbuf;
              locals.l_outbytesleft = *outbytesleft;
              locals.l_errno = 0;
              wcd->parent.fallbacks.mb_to_wc_fallback(*inbuf, incount,
                                                      mb_to_wc_write_replacement,
                                                      &locals,
                                                      wcd->parent.fallbacks.data);
              if (locals.l_errno != 0) {
                errno = locals.l_errno;
                return -1;
              }
              /* Restoring the state is not needed because it is the initial
                 state anyway: For all known locale encodings, the multibyte
                 to wchar_t conversion doesn't have shift state, and we have
                 excluded partial accumulated characters. */
              /* wcd->state = state; */
              *inbuf += incount;
              *inbytesleft -= incount;
              *outbuf = locals.l_outbuf;
              *outbytesleft = locals.l_outbytesleft;
              result += 1;
              break;
            }
            #endif
            else
              return -1;
          } else {
            if (*outbytesleft < sizeof(wchar_t)) {
              errno = E2BIG;
              return -1;
            }
            *(wchar_t*) *outbuf = wc;
            /* Restoring the state is not needed because it is the initial
               state anyway: For all known locale encodings, the multibyte
               to wchar_t conversion doesn't have shift state, and we have
               excluded partial accumulated characters. */
            /* wcd->state = state; */
            *outbuf += sizeof(wchar_t);
            *outbytesleft -= sizeof(wchar_t);
          }
          *inbuf += incount;
          *inbytesleft -= incount;
          result += res;
          break;
        }
      }
      incount++;
      if (incount > *inbytesleft) {
        /* Incomplete input. */
        errno = EINVAL;
        return -1;
      }
    }
  }
  return result;
}