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
struct TYPE_3__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* wc_to_mb_fallback ) (int /*<<< orphan*/  const,int /*<<< orphan*/ ,struct wc_to_mb_fallback_locals*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ fallbacks; scalar_t__ discard_ilseq; } ;
struct wchar_conv_struct {void* state; TYPE_2__ parent; } ;
struct wc_to_mb_fallback_locals {char* l_outbuf; size_t l_outbytesleft; scalar_t__ l_errno; } ;
typedef  void* mbstate_t ;
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 int BUF_SIZE ; 
 scalar_t__ E2BIG ; 
 scalar_t__ EILSEQ ; 
 scalar_t__ EINVAL ; 
 int MB_CUR_MAX ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const,int /*<<< orphan*/ ,struct wc_to_mb_fallback_locals*,int /*<<< orphan*/ ) ; 
 size_t unicode_loop_convert (TYPE_2__*,char const**,size_t*,char**,size_t*) ; 
 int /*<<< orphan*/  wc_to_mb_write_replacement ; 
 size_t wcrtomb (char*,int /*<<< orphan*/  const,void**) ; 

__attribute__((used)) static size_t wchar_from_loop_convert (iconv_t icd,
                                       const char* * inbuf, size_t *inbytesleft,
                                       char* * outbuf, size_t *outbytesleft)
{
  struct wchar_conv_struct * wcd = (struct wchar_conv_struct *) icd;
  size_t result = 0;
  while (*inbytesleft >= sizeof(wchar_t)) {
    const wchar_t * inptr = (const wchar_t *) *inbuf;
    size_t inleft = *inbytesleft;
    char buf[BUF_SIZE];
    mbstate_t state = wcd->state;
    size_t bufcount = 0;
    while (inleft >= sizeof(wchar_t)) {
      /* Convert one wchar_t to multibyte representation. */
      size_t count = wcrtomb(buf+bufcount,*inptr,&state);
      if (count == (size_t)(-1)) {
        /* Invalid input. */
        if (wcd->parent.discard_ilseq) {
          count = 0;
        }
        #ifndef LIBICONV_PLUG
        else if (wcd->parent.fallbacks.wc_to_mb_fallback != NULL) {
          /* Drop the contents of buf[] accumulated so far, and instead
             pass all queued wide characters to the fallback handler. */
          struct wc_to_mb_fallback_locals locals;
          const wchar_t * fallback_inptr;
          #if 0
          locals.l_wcd = wcd;
          #endif
          locals.l_outbuf = *outbuf;
          locals.l_outbytesleft = *outbytesleft;
          locals.l_errno = 0;
          for (fallback_inptr = (const wchar_t *) *inbuf;
               fallback_inptr <= inptr;
               fallback_inptr++)
            wcd->parent.fallbacks.wc_to_mb_fallback(*fallback_inptr,
                                                    wc_to_mb_write_replacement,
                                                    &locals,
                                                    wcd->parent.fallbacks.data);
          if (locals.l_errno != 0) {
            errno = locals.l_errno;
            return -1;
          }
          wcd->state = state;
          *inbuf = (const char *) (inptr + 1);
          *inbytesleft = inleft - sizeof(wchar_t);
          *outbuf = locals.l_outbuf;
          *outbytesleft = locals.l_outbytesleft;
          result += 1;
          break;
        }
        #endif
        else {
          errno = EILSEQ;
          return -1;
        }
      }
      inptr++;
      inleft -= sizeof(wchar_t);
      bufcount += count;
      if (count == 0) {
        /* Continue, append next wchar_t. */
      } else {
        /* Attempt to convert the accumulated multibyte representations
           to the target encoding. */
        const char* bufptr = buf;
        size_t bufleft = bufcount;
        char* outptr = *outbuf;
        size_t outleft = *outbytesleft;
        size_t res = unicode_loop_convert(&wcd->parent,
                                          &bufptr,&bufleft,
                                          &outptr,&outleft);
        if (res == (size_t)(-1)) {
          if (errno == EILSEQ)
            /* Invalid input. */
            return -1;
          else if (errno == E2BIG)
            /* Output buffer too small. */
            return -1;
          else if (errno == EINVAL) {
            /* Continue, append next wchar_t, but avoid buffer overrun. */
            if (bufcount + MB_CUR_MAX > BUF_SIZE)
              abort();
          } else
            abort();
        } else {
          /* Successful conversion. */
          wcd->state = state;
          *inbuf = (const char *) inptr;
          *inbytesleft = inleft;
          *outbuf = outptr;
          *outbytesleft = outleft;
          result += res;
          break;
        }
      }
    }
  }
  return result;
}