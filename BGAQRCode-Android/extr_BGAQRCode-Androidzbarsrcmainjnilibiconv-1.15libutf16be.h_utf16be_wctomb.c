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
 int RET_ILUNI ; 
 int RET_TOOSMALL ; 

__attribute__((used)) static int
utf16be_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  if (!(wc >= 0xd800 && wc < 0xe000)) {
    if (wc < 0x10000) {
      if (n >= 2) {
        r[0] = (unsigned char) (wc >> 8);
        r[1] = (unsigned char) wc;
        return 2;
      } else
        return RET_TOOSMALL;
    }
    else if (wc < 0x110000) {
      if (n >= 4) {
        ucs4_t wc1 = 0xd800 + ((wc - 0x10000) >> 10);
        ucs4_t wc2 = 0xdc00 + ((wc - 0x10000) & 0x3ff);
        r[0] = (unsigned char) (wc1 >> 8);
        r[1] = (unsigned char) wc1;
        r[2] = (unsigned char) (wc2 >> 8);
        r[3] = (unsigned char) wc2;
        return 4;
      } else
        return RET_TOOSMALL;
    }
  }
  return RET_ILUNI;
}