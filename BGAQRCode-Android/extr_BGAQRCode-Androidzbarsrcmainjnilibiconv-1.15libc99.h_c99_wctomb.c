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
typedef  int ucs4_t ;
typedef  int /*<<< orphan*/  conv_t ;

/* Variables and functions */
 int RET_TOOSMALL ; 

__attribute__((used)) static int
c99_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  if (wc < 0xa0) {
    *r = wc;
    return 1;
  } else {
    int result;
    unsigned char u;
    if (wc < 0x10000) {
      result = 6;
      u = 'u';
    } else {
      result = 10;
      u = 'U';
    }
    if (n >= result) {
      int count;
      r[0] = '\\';
      r[1] = u;
      r += 2;
      for (count = result-3; count >= 0; count--) {
        unsigned int i = (wc >> (4*count)) & 0x0f;
        *r++ = (i < 10 ? '0'+i : 'a'-10+i);
      }
      return result;
    } else
      return RET_TOOSMALL;
  }
}