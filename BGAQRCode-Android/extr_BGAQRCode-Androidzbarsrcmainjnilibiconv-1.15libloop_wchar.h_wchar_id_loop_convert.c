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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* wc_hook ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct conv_struct {TYPE_1__ hooks; } ;
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t wchar_id_loop_convert (iconv_t icd,
                                     const char* * inbuf, size_t *inbytesleft,
                                     char* * outbuf, size_t *outbytesleft)
{
  struct conv_struct * cd = (struct conv_struct *) icd;
  const wchar_t* inptr = (const wchar_t*) *inbuf;
  size_t inleft = *inbytesleft / sizeof(wchar_t);
  wchar_t* outptr = (wchar_t*) *outbuf;
  size_t outleft = *outbytesleft / sizeof(wchar_t);
  size_t count = (inleft <= outleft ? inleft : outleft);
  if (count > 0) {
    *inbytesleft -= count * sizeof(wchar_t);
    *outbytesleft -= count * sizeof(wchar_t);
    do {
      wchar_t wc = *inptr++;
      *outptr++ = wc;
      #ifndef LIBICONV_PLUG
      if (cd->hooks.wc_hook)
        (*cd->hooks.wc_hook)(wc, cd->hooks.data);
      #endif
    } while (--count > 0);
    *inbuf = (const char*) inptr;
    *outbuf = (char*) outptr;
  }
  return 0;
}