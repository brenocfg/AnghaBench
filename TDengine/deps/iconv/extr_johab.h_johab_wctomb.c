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
 int RET_TOOSMALL ; 
 int /*<<< orphan*/  abort () ; 
 int johab_hangul_wctomb (int /*<<< orphan*/ ,unsigned char*,int,int) ; 
 int ksc5601_wctomb (int /*<<< orphan*/ ,unsigned char*,int,int) ; 

__attribute__((used)) static int
johab_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, int n)
{
  unsigned char buf[2];
  int ret;

  /* Try ASCII variation. */
  if (wc < 0x0080 && wc != 0x005c) {
    *r = wc;
    return 1;
  }
  if (wc == 0x20a9) {
    *r = 0x5c;
    return 1;
  }

  /* Try JOHAB Hangul table before KSC5601 table, because the KSC5601 table
     contains some (2350 out of 11172) Hangul syllables (rows 0x30XX..0x48XX),
     and we want the search to return the JOHAB Hangul table entry. */

  /* Try JOHAB Hangul. */
  ret = johab_hangul_wctomb(conv,buf,wc,2);
  if (ret != RET_ILUNI) {
    if (ret != 2) abort();
    if (n < 2)
      return RET_TOOSMALL;
    r[0] = buf[0];
    r[1] = buf[1];
    return 2;
  }

  /* Try KSC5601, now KS X 1001. */
  ret = ksc5601_wctomb(conv,buf,wc,2);
  if (ret != RET_ILUNI) {
    unsigned char c1, c2;
    if (ret != 2) abort();
    if (n < 2)
      return RET_TOOSMALL;
    c1 = buf[0];
    c2 = buf[1];
    if (((c1 >= 0x21 && c1 <= 0x2c) || (c1 >= 0x4a && c1 <= 0x7d))
        && (c2 >= 0x21 && c2 <= 0x7e)) {
      unsigned int t = (c1 < 0x4A ? (c1-0x21+0x1B2) : (c1-0x21+0x197));
      unsigned char t2 = ((t & 1) ? 0x5e : 0) + (c2 - 0x21);
      r[0] = t >> 1;
      r[1] = (t2 < 0x4e ? t2+0x31 : t2+0x43);
      return 2;
    }
  }

  return RET_ILUNI;
}