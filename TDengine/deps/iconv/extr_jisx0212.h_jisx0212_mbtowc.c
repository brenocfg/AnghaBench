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
 unsigned short* jisx0212_2uni_page22 ; 
 unsigned short* jisx0212_2uni_page26 ; 
 unsigned short* jisx0212_2uni_page29 ; 
 unsigned short* jisx0212_2uni_page30 ; 

__attribute__((used)) static int
jisx0212_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  unsigned char c1 = s[0];
  if ((c1 == 0x22) || (c1 >= 0x26 && c1 <= 0x27) || (c1 >= 0x29 && c1 <= 0x2b) || (c1 >= 0x30 && c1 <= 0x6d)) {
    if (n >= 2) {
      unsigned char c2 = s[1];
      if (c2 >= 0x21 && c2 < 0x7f) {
        unsigned int i = 94 * (c1 - 0x21) + (c2 - 0x21);
        unsigned short wc = 0xfffd;
        if (i < 470) {
          if (i < 175)
            wc = jisx0212_2uni_page22[i-94];
        } else if (i < 752) {
          if (i < 658)
            wc = jisx0212_2uni_page26[i-470];
        } else if (i < 1410) {
          if (i < 1027)
            wc = jisx0212_2uni_page29[i-752];
        } else {
          if (i < 7211)
            wc = jisx0212_2uni_page30[i-1410];
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