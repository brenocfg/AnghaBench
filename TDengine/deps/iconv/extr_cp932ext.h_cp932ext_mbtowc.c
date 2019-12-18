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
typedef  scalar_t__ ucs4_t ;
typedef  int /*<<< orphan*/  conv_t ;

/* Variables and functions */
 int RET_ILSEQ ; 
 int RET_TOOFEW (int /*<<< orphan*/ ) ; 
 unsigned short* cp932ext_2uni_page87 ; 
 unsigned short* cp932ext_2uni_pageed ; 
 unsigned short* cp932ext_2uni_pagefa ; 

__attribute__((used)) static int
cp932ext_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  unsigned char c1 = s[0];
  if ((c1 == 0x87) || (c1 >= 0xed && c1 <= 0xee) || (c1 >= 0xfa && c1 <= 0xfc)) {
    if (n >= 2) {
      unsigned char c2 = s[1];
      if ((c2 >= 0x40 && c2 < 0x7f) || (c2 >= 0x80 && c2 < 0xfd)) {
        unsigned int i = 188 * (c1 - (c1 >= 0xe0 ? 0xc1 : 0x81)) + (c2 - (c2 >= 0x80 ? 0x41 : 0x40));
        unsigned short wc = 0xfffd;
        if (i < 8272) {
          if (i < 1220)
            wc = cp932ext_2uni_page87[i-1128];
        } else if (i < 10716) {
          if (i < 8648)
            wc = cp932ext_2uni_pageed[i-8272];
        } else {
          if (i < 11104)
            wc = cp932ext_2uni_pagefa[i-10716];
        }
        if (wc != 0xfffd) {
          *pwc = (ucs4_t) wc;
          return 2;
        }
      }
      return RET_ILSEQ;
    }
    return RET_TOOFEW(0);
  }
  return RET_ILSEQ;
}