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
 unsigned short* gb18030ext_2uni_pagea9 ; 
 unsigned short* gb18030ext_2uni_pagefe ; 

__attribute__((used)) static int
gb18030ext_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  unsigned char c1 = s[0];
  if ((c1 == 0xa2) || (c1 >= 0xa4 && c1 <= 0xa9) || (c1 == 0xd7) || (c1 == 0xfe)) {
    if (n >= 2) {
      unsigned char c2 = s[1];
      if ((c2 >= 0x40 && c2 < 0x7f) || (c2 >= 0x80 && c2 < 0xff)) {
        unsigned int i = 190 * (c1 - 0x81) + (c2 - (c2 >= 0x80 ? 0x41 : 0x40));
        unsigned short wc = 0xfffd;
        switch (c1) {
          case 0xa2:
            if (i >= 6376 && i <= 6381) /* 0xA2AB..0xA2B0 */
              wc = 0xe766 + (i - 6376);
            else if (i == 6432) /* 0xA2E3 */
              wc = 0x20ac;
            else if (i == 6433) /* 0xA2E4 */
              wc = 0xe76d;
            else if (i >= 6444 && i <= 6445) /* 0xA2EF..0xA2F0 */
              wc = 0xe76e + (i - 6444);
            else if (i >= 6458 && i <= 6459) /* 0xA2FD..0xA2FE */
              wc = 0xe770 + (i - 6458);
            break;
          case 0xa4:
            if (i >= 6829 && i <= 6839) /* 0xA4F4..0xA4FE */
              wc = 0xe772 + (i - 6829);
            break;
          case 0xa5:
            if (i >= 7022 && i <= 7029) /* 0xA5F7..0xA5FE */
              wc = 0xe77d + (i - 7022);
            break;
          case 0xa6:
            if (i >= 7150 && i <= 7157) /* 0xA6B9..0xA6C0 */
              wc = 0xe785 + (i - 7150);
            else if (i >= 7182 && i <= 7190) /* 0xA6D9..0xA6DF */
              wc = 0xe78d + (i - 7182);
            else if (i >= 7201 && i <= 7202) /* 0xA6EC..0xA6ED */
              wc = 0xe794 + (i - 7201);
            else if (i == 7208) /* 0xA6F3 */
              wc = 0xe796;
            else if (i >= 7211 && i <= 7219) /* 0xA6F6..0xA6FE */
              wc = 0xe797 + (i - 7211);
            break;
          case 0xa7:
            if (i >= 7349 && i <= 7363) /* 0xA7C2..0xA7D0 */
              wc = 0xe7a0 + (i - 7349);
            else if (i >= 7397 && i <= 7409) /* 0xA7F2..0xA7FE */
              wc = 0xe7af + (i - 7397);
            break;
          case 0xa8:
            if (i >= 7495 && i <= 7505) /* 0xA896..0xA8A0 */
              wc = 0xe7bc + (i - 7495);
            else if (i == 7533) /* 0xA8BC */
              wc = 0xe7c7;
            else if (i == 7536) /* 0xA8BF */
              wc = 0x01f9;
            else if (i >= 7538 && i <= 7541) /* 0xA8C1..0xA8C4 */
              wc = 0xe7c9 + (i - 7538);
            else if (i >= 7579 && i <= 7599) /* 0xA8EA..0xA8FE */
              wc = 0xe7cd + (i - 7579);
            break;
          case 0xa9:
            if (i == 7624) /* 0xA958 */
              wc = 0xe7e2;
            else if (i == 7627) /* 0xA95B */
              wc = 0xe7e3;
            else if (i >= 7629 && i <= 7631) /* 0xA95D..0xA95F */
              wc = 0xe7e4 + (i - 7629);
            else if (i >= 7672 && i < 7685) /* 0xA989..0xA995 */
              wc = gb18030ext_2uni_pagea9[i-7672];
            else if (i >= 7686 && i <= 7698) /* 0xA997..0xA9A3 */
              wc = 0xe7f4 + (i - 7686);
            else if (i >= 7775 && i <= 7789) /* 0xA9F0..0xA9FE */
              wc = 0xe801 + (i - 7775);
            break;
          case 0xd7:
            if (i >= 16525 && i <= 16529) /* 0xD7FA..0xD7FE */
              wc = 0xe810 + (i - 16525);
            break;
          case 0xfe:
            if (i < 23846)
              wc = gb18030ext_2uni_pagefe[i-23750];
            break;
          default:
            break;
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