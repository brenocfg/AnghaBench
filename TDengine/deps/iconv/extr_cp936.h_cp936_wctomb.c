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
 int RET_ILUNI ; 
 int RET_TOOFEW (int /*<<< orphan*/ ) ; 
 int ces_gbk_wctomb (int /*<<< orphan*/ ,unsigned char*,int,int) ; 

__attribute__((used)) static int
cp936_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, int n)
{
  /* Try GBK first. */
  {
    int ret = ces_gbk_wctomb(conv,r,wc,n);
    if (ret != RET_ILUNI)
      return ret;
  }
  /* Then handle the additional mappings. */
  if (wc >= 0xe000 && wc < 0xe586) {
    /* User-defined characters */
    if (n < 2)
      return RET_TOOFEW(0);
    if (wc < 0xe4c6) {
      unsigned int i = wc - 0xe000;
      unsigned int c1 = i / 94;
      unsigned int c2 = i % 94;
      r[0] = c1 + (c1 < 6 ? 0xaa : 0xf2);
      r[1] = c2 + 0xa1;
      return 2;
    } else {
      unsigned int i = wc - 0xe4c6;
      unsigned int c1 = i / 96;
      unsigned int c2 = i % 96;
      r[0] = c1 + 0xa1;
      r[1] = c2 + (c2 < 0x3f ? 0x40 : 0x41);
      return 2;
    }
  } else if (wc == 0x20ac) {
    r[0] = 0x80;
    return 1;
  }
  return RET_ILUNI;
}