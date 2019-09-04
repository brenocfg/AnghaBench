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
 unsigned short* cp50221_0212_ext_2uni ; 

__attribute__((used)) static int
cp50221_0212_ext_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, size_t n)
{
  unsigned char c = *s;
  if (c < 0x70) {
    unsigned short wc = cp50221_0212_ext_2uni[c];
    if (wc != 0xfffd) {
      *pwc = (ucs4_t) wc;
      return 1;
    }
  }
  else if (c == 0xa1) {
    *pwc = 0x974d;
    return 1;
  }
  return RET_ILSEQ;
}