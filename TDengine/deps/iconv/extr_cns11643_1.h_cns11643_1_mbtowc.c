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
 unsigned short* cns11643_1_2uni_page21 ; 
 unsigned short* cns11643_1_2uni_page42 ; 
 unsigned short* cns11643_1_2uni_page44 ; 

__attribute__((used)) static int
cns11643_1_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  unsigned char c1 = s[0];
  if ((c1 >= 0x21 && c1 <= 0x27) || (c1 == 0x42) || (c1 >= 0x44 && c1 <= 0x7d)) {
    if (n >= 2) {
      unsigned char c2 = s[1];
      if (c2 >= 0x21 && c2 < 0x7f) {
        unsigned int i = 94 * (c1 - 0x21) + (c2 - 0x21);
        unsigned short wc = 0xfffd;
        if (i < 3102) {
          if (i < 500)
            wc = cns11643_1_2uni_page21[i];
          else if (i == 571)
            wc = 0x4ea0;
          else if (i == 578)
            wc = 0x51ab;
          else if (i == 583)
            wc = 0x52f9;
        } else if (i < 3290) {
          if (i < 3136)
            wc = cns11643_1_2uni_page42[i-3102];
        } else {
          if (i < 8691)
            wc = cns11643_1_2uni_page44[i-3290];
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