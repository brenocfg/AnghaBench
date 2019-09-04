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
 scalar_t__* cp864_2uni_1 ; 
 unsigned short* cp864_2uni_2 ; 

__attribute__((used)) static int
cp864_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, size_t n)
{
  unsigned char c = *s;
  if (c < 0x20) {
    *pwc = (ucs4_t) c;
    return 1;
  }
  else if (c < 0x30) {
    *pwc = (ucs4_t) cp864_2uni_1[c-0x20];
    return 1;
  }
  else if (c < 0x80) {
    *pwc = (ucs4_t) c;
    return 1;
  }
  else {
    unsigned short wc = cp864_2uni_2[c-0x80];
    if (wc != 0xfffd) {
      *pwc = (ucs4_t) wc;
      return 1;
    }
  }
  return RET_ILSEQ;
}