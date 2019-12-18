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
 scalar_t__* uhc_2_2uni_main_pagea1 ; 
 scalar_t__* uhc_2_2uni_pagea1 ; 

__attribute__((used)) static int
uhc_2_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  unsigned char c1 = s[0];
  if ((c1 >= 0xa1 && c1 <= 0xc6)) {
    if (n >= 2) {
      unsigned char c2 = s[1];
      if ((c2 >= 0x41 && c2 < 0x5b) || (c2 >= 0x61 && c2 < 0x7b) || (c2 >= 0x81 && c2 < 0xa1)) {
        unsigned int row = c1 - 0xa1;
        unsigned int col = c2 - (c2 >= 0x81 ? 0x4d : c2 >= 0x61 ? 0x47 : 0x41);
        unsigned int i = 84 * row + col;
        if (i < 3126) {
          *pwc = (ucs4_t) (uhc_2_2uni_main_pagea1[2*row+(col>=42?1:0)] + uhc_2_2uni_pagea1[i]);
          return 2;
        }
      }
      return RET_ILSEQ;
    }
    return RET_TOOFEW(0);
  }
  return RET_ILSEQ;
}