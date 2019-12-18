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
typedef  int cppchar_t ;

/* Variables and functions */
 int E2BIG ; 

__attribute__((used)) static inline int
one_cppchar_to_utf8 (cppchar_t c, uchar **outbufp, size_t *outbytesleftp)
{
  static const uchar masks[6] =  { 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };
  static const uchar limits[6] = { 0x80, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE };
  size_t nbytes;
  uchar buf[6], *p = &buf[6];
  uchar *outbuf = *outbufp;

  nbytes = 1;
  if (c < 0x80)
    *--p = c;
  else
    {
      do
	{
	  *--p = ((c & 0x3F) | 0x80);
	  c >>= 6;
	  nbytes++;
	}
      while (c >= 0x3F || (c & limits[nbytes-1]));
      *--p = (c | masks[nbytes-1]);
    }

  if (*outbytesleftp < nbytes)
    return E2BIG;

  while (p < &buf[6])
    *outbuf++ = *p++;
  *outbytesleftp -= nbytes;
  *outbufp = outbuf;
  return 0;
}