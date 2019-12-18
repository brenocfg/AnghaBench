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
typedef  int uchar ;
typedef  scalar_t__ iconv_t ;
typedef  int cppchar_t ;

/* Variables and functions */
 int E2BIG ; 
 int one_utf8_to_cppchar (int const**,size_t*,int*) ; 

__attribute__((used)) static inline int
one_utf8_to_utf32 (iconv_t bigend, const uchar **inbufp, size_t *inbytesleftp,
		   uchar **outbufp, size_t *outbytesleftp)
{
  uchar *outbuf;
  cppchar_t s = 0;
  int rval;

  /* Check for space first, since we know exactly how much we need.  */
  if (*outbytesleftp < 4)
    return E2BIG;

  rval = one_utf8_to_cppchar (inbufp, inbytesleftp, &s);
  if (rval)
    return rval;

  outbuf = *outbufp;
  outbuf[bigend ? 3 : 0] = (s & 0x000000FF);
  outbuf[bigend ? 2 : 1] = (s & 0x0000FF00) >> 8;
  outbuf[bigend ? 1 : 2] = (s & 0x00FF0000) >> 16;
  outbuf[bigend ? 0 : 3] = (s & 0xFF000000) >> 24;

  *outbufp += 4;
  *outbytesleftp -= 4;
  return 0;
}