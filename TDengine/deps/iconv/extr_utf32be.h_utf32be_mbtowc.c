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

__attribute__((used)) static int
utf32be_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  if (n >= 4) {
    ucs4_t wc = (s[0] << 24) + (s[1] << 16) + (s[2] << 8) + s[3];
    if (wc < 0x110000 && !(wc >= 0xd800 && wc < 0xe000)) {
      *pwc = wc;
      return 4;
    } else
      return RET_ILSEQ;
  }
  return RET_TOOFEW(0);
}