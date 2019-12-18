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
 int RET_ILSEQ ; 
 int RET_TOOFEW (int /*<<< orphan*/ ) ; 
 int ascii_mbtowc (int /*<<< orphan*/ ,int*,unsigned char const*,int) ; 
 unsigned short* big5_2003_2uni_pagea1 ; 
 unsigned short* big5_2003_2uni_pagec6 ; 
 int* big5_2003_2uni_pagef9 ; 
 int big5_mbtowc (int /*<<< orphan*/ ,int*,unsigned char const*,int) ; 

__attribute__((used)) static int
big5_2003_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  unsigned char c = *s;
  /* Code set 0 (ASCII) */
  if (c < 0x80)
    return ascii_mbtowc(conv,pwc,s,n);
  /* Code set 1 (BIG5 extended) */
  if (c >= 0x81 && c < 0xff) {
    if (n < 2)
      return RET_TOOFEW(0);
    {
      unsigned char c2 = s[1];
      if ((c2 >= 0x40 && c2 < 0x7f) || (c2 >= 0xa1 && c2 < 0xff)) {
        if (c >= 0xa1) {
          if (c < 0xa3) {
            unsigned int i = 157 * (c - 0xa1) + (c2 - (c2 >= 0xa1 ? 0x62 : 0x40));
            unsigned short wc = big5_2003_2uni_pagea1[i];
            if (wc != 0xfffd) {
              *pwc = (ucs4_t) wc;
              return 2;
            }
          }
          if (!((c == 0xc6 && c2 >= 0xa1) || c == 0xc7)) {
            if (!(c == 0xc2 && c2 == 0x55)) {
              int ret = big5_mbtowc(conv,pwc,s,2);
              if (ret != RET_ILSEQ)
                return ret;
              if (c == 0xa3) {
                if (c2 >= 0xc0 && c2 <= 0xe1) {
                  *pwc = (c2 == 0xe1 ? 0x20ac : c2 == 0xe0 ? 0x2421 : 0x2340 + c2);
                  return 2;
                }
              } else if (c == 0xf9) {
                if (c2 >= 0xd6) {
                  *pwc = big5_2003_2uni_pagef9[c2-0xd6];
                  return 2;
                }
              } else if (c >= 0xfa) {
                *pwc = 0xe000 + 157 * (c - 0xfa) + (c2 - (c2 >= 0xa1 ? 0x62 : 0x40));
                return 2;
              }
            } else {
              /* c == 0xc2 && c2 == 0x55. */
              *pwc = 0x5f5e;
              return 2;
            }
          } else {
            /* (c == 0xc6 && c2 >= 0xa1) || c == 0xc7. */
            unsigned int i = 157 * (c - 0xc6) + (c2 - (c2 >= 0xa1 ? 0x62 : 0x40));
            if (i < 133) {
              /* 63 <= i < 133. */
              unsigned short wc = big5_2003_2uni_pagec6[i-63];
              if (wc != 0xfffd) {
                *pwc = (ucs4_t) wc;
                return 2;
              }
            } else if (i < 216) {
              /* 133 <= i < 216. Hiragana. */
              *pwc = 0x3041 - 133 + i;
              return 2;
            } else if (i < 302) {
              /* 216 <= i < 302. Katakana. */
              *pwc = 0x30a1 - 216 + i;
              return 2;
            }
          }
        } else {
          /* 0x81 <= c < 0xa1. */
          *pwc = (c >= 0x8e ? 0xdb18 : 0xeeb8) + 157 * (c - 0x81)
                 + (c2 - (c2 >= 0xa1 ? 0x62 : 0x40));
          return 2;
        }
      }
    }
  }
  return RET_ILSEQ;
}