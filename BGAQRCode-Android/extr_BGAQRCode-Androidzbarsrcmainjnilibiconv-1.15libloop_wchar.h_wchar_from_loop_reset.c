#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct wchar_conv_struct {int /*<<< orphan*/  parent; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 int BUF_SIZE ; 
 scalar_t__ E2BIG ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  mbsinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 
 size_t unicode_loop_convert (int /*<<< orphan*/ *,char const**,size_t*,char**,size_t*) ; 
 size_t unicode_loop_reset (int /*<<< orphan*/ *,char**,size_t*) ; 
 size_t wcrtomb (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t wchar_from_loop_reset (iconv_t icd,
                                     char* * outbuf, size_t *outbytesleft)
{
  struct wchar_conv_struct * wcd = (struct wchar_conv_struct *) icd;
  if (outbuf == NULL || *outbuf == NULL) {
    /* Reset the states. */
    memset(&wcd->state,'\0',sizeof(mbstate_t));
    return unicode_loop_reset(&wcd->parent,NULL,NULL);
  } else {
    if (!mbsinit(&wcd->state)) {
      mbstate_t state = wcd->state;
      char buf[BUF_SIZE];
      size_t bufcount = wcrtomb(buf,(wchar_t)0,&state);
      if (bufcount == (size_t)(-1) || bufcount == 0 || buf[bufcount-1] != '\0')
        abort();
      else {
        const char* bufptr = buf;
        size_t bufleft = bufcount-1;
        char* outptr = *outbuf;
        size_t outleft = *outbytesleft;
        size_t res = unicode_loop_convert(&wcd->parent,
                                          &bufptr,&bufleft,
                                          &outptr,&outleft);
        if (res == (size_t)(-1)) {
          if (errno == E2BIG)
            return -1;
          else
            abort();
        } else {
          res = unicode_loop_reset(&wcd->parent,&outptr,&outleft);
          if (res == (size_t)(-1))
            return res;
          else {
            /* Successful. */
            wcd->state = state;
            *outbuf = outptr;
            *outbytesleft = outleft;
            return 0;
          }
        }
      }
    } else
      return unicode_loop_reset(&wcd->parent,outbuf,outbytesleft);
  }
}