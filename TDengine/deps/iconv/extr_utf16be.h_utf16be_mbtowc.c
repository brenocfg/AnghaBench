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
 int RET_SHIFT_ILSEQ (int) ; 
 int RET_TOOFEW (int) ; 

__attribute__((used)) static int
utf16be_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  int count = 0;
  if (n >= 2) {
    ucs4_t wc = (s[0] << 8) + s[1];
    if (wc >= 0xd800 && wc < 0xdc00) {
      if (n >= 4) {
        ucs4_t wc2 = (s[2] << 8) + s[3];
        if (!(wc2 >= 0xdc00 && wc2 < 0xe000))
          goto ilseq;
        *pwc = 0x10000 + ((wc - 0xd800) << 10) + (wc2 - 0xdc00);
        return count+4;
      }
    } else if (wc >= 0xdc00 && wc < 0xe000) {
      goto ilseq;
    } else {
      *pwc = wc;
      return count+2;
    }
  }
  return RET_TOOFEW(count);

ilseq:
  return RET_SHIFT_ILSEQ(count);
}