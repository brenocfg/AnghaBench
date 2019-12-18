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
 int ascii_wctomb (int /*<<< orphan*/ ,unsigned char*,int,int) ; 
 int jisx0201_wctomb (int /*<<< orphan*/ ,unsigned char*,int,int) ; 
 int jisx0208_wctomb (int /*<<< orphan*/ ,unsigned char*,int,int) ; 
 int jisx0212_wctomb (int /*<<< orphan*/ ,unsigned char*,int,int) ; 

__attribute__((used)) static int
euc_jp_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, int n)
{
  unsigned char buf[2];
  int ret;

  /* Code set 0 (ASCII or JIS X 0201-1976 Roman) */
  ret = ascii_wctomb(conv,r,wc,n);
  if (ret != RET_ILUNI)
    return ret;

  /* Code set 1 (JIS X 0208) */
  ret = jisx0208_wctomb(conv,buf,wc,2);
  if (ret != RET_ILUNI) {
    if (ret != 2) abort();
    if (n < 2)
      return RET_TOOSMALL;
    r[0] = buf[0]+0x80;
    r[1] = buf[1]+0x80;
    return 2;
  }

  /* Code set 2 (half-width katakana) */
  ret = jisx0201_wctomb(conv,buf,wc,1);
  if (ret != RET_ILUNI && buf[0] >= 0x80) {
    if (ret != 1) abort();
    if (n < 2)
      return RET_TOOSMALL;
    r[0] = 0x8e;
    r[1] = buf[0];
    return 2;
  }

  /* Code set 3 (JIS X 0212-1990) */
  ret = jisx0212_wctomb(conv,buf,wc,2);
  if (ret != RET_ILUNI) {
    if (ret != 2) abort();
    if (n < 3)
      return RET_TOOSMALL;
    r[0] = 0x8f;
    r[1] = buf[0]+0x80;
    r[2] = buf[1]+0x80;
    return 3;
  }

  /* Extra compatibility with Shift_JIS.  */
  if (wc == 0x00a5) {
    r[0] = 0x5c;
    return 1;
  }
  if (wc == 0x203e) {
    r[0] = 0x7e;
    return 1;
  }

  /* User-defined range. See
   * Ken Lunde's "CJKV Information Processing", table 4-66, p. 206. */
  if (wc >= 0xe000 && wc < 0xe758) {
    if (wc < 0xe3ac) {
      unsigned char c1, c2;
      if (n < 2)
        return RET_TOOSMALL;
      c1 = (unsigned int) (wc - 0xe000) / 94;
      c2 = (unsigned int) (wc - 0xe000) % 94;
      r[0] = c1+0xf5;
      r[1] = c2+0xa1;
      return 2;
    } else {
      unsigned char c1, c2;
      if (n < 3)
        return RET_TOOSMALL;
      c1 = (unsigned int) (wc - 0xe3ac) / 94;
      c2 = (unsigned int) (wc - 0xe3ac) % 94;
      r[0] = 0x8f;
      r[1] = c1+0xf5;
      r[2] = c2+0xa1;
      return 3;
    }
  }

  return RET_ILUNI;
}