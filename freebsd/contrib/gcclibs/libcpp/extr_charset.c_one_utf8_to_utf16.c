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
 int EILSEQ ; 
 int one_utf8_to_cppchar (int const**,size_t*,int*) ; 

__attribute__((used)) static inline int
one_utf8_to_utf16 (iconv_t bigend, const uchar **inbufp, size_t *inbytesleftp,
		   uchar **outbufp, size_t *outbytesleftp)
{
  int rval;
  cppchar_t s = 0;
  const uchar *save_inbuf = *inbufp;
  size_t save_inbytesleft = *inbytesleftp;
  uchar *outbuf = *outbufp;

  rval = one_utf8_to_cppchar (inbufp, inbytesleftp, &s);
  if (rval)
    return rval;

  if (s > 0x0010FFFF)
    {
      *inbufp = save_inbuf;
      *inbytesleftp = save_inbytesleft;
      return EILSEQ;
    }

  if (s < 0xFFFF)
    {
      if (*outbytesleftp < 2)
	{
	  *inbufp = save_inbuf;
	  *inbytesleftp = save_inbytesleft;
	  return E2BIG;
	}
      outbuf[bigend ? 1 : 0] = (s & 0x00FF);
      outbuf[bigend ? 0 : 1] = (s & 0xFF00) >> 8;

      *outbufp += 2;
      *outbytesleftp -= 2;
      return 0;
    }
  else
    {
      cppchar_t hi, lo;

      if (*outbytesleftp < 4)
	{
	  *inbufp = save_inbuf;
	  *inbytesleftp = save_inbytesleft;
	  return E2BIG;
	}

      hi = (s - 0x10000) / 0x400 + 0xD800;
      lo = (s - 0x10000) % 0x400 + 0xDC00;

      /* Even if we are little-endian, put the high surrogate first.
	 ??? Matches practice?  */
      outbuf[bigend ? 1 : 0] = (hi & 0x00FF);
      outbuf[bigend ? 0 : 1] = (hi & 0xFF00) >> 8;
      outbuf[bigend ? 3 : 2] = (lo & 0x00FF);
      outbuf[bigend ? 2 : 3] = (lo & 0xFF00) >> 8;

      *outbufp += 4;
      *outbytesleftp -= 4;
      return 0;
    }
}