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

/* Variables and functions */
 char* base64 ; 
 unsigned char curlx_ultouc (unsigned long) ; 

__attribute__((used)) static size_t decodeQuantum(unsigned char *dest, const char *src)
{
  size_t padding = 0;
  const char *s, *p;
  unsigned long i, x = 0;

  for(i = 0, s = src; i < 4; i++, s++) {
    if(*s == '=') {
      x = (x << 6);
      padding++;
    }
    else {
      unsigned long v = 0;
      p = base64;

      while(*p && (*p != *s)) {
        v++;
        p++;
      }

      if(*p == *s)
        x = (x << 6) + v;
      else
        return 0;
    }
  }

  if(padding < 1)
    dest[2] = curlx_ultouc(x & 0xFFUL);

  x >>= 8;
  if(padding < 2)
    dest[1] = curlx_ultouc(x & 0xFFUL);

  x >>= 8;
  dest[0] = curlx_ultouc(x & 0xFFUL);

  return 3 - padding;
}