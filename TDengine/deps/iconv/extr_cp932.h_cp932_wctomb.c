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
 int cp932ext_wctomb (int /*<<< orphan*/ ,unsigned char*,int,int) ; 
 int jisx0201_wctomb (int /*<<< orphan*/ ,unsigned char*,int,int) ; 
 int jisx0208_wctomb (int /*<<< orphan*/ ,unsigned char*,int,int) ; 

__attribute__((used)) static int
cp932_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, int n)
{
  unsigned char buf[2];
  int ret;

  /* Try ASCII. */
  ret = ascii_wctomb(conv,buf,wc,1);
  if (ret != RET_ILUNI) {
    unsigned char c;
    if (ret != 1) abort();
    c = buf[0];
    if (c < 0x80) {
      r[0] = c;
      return 1;
    }
  }

  /* Try JIS X 0201-1976 Katakana. */
  ret = jisx0201_wctomb(conv,buf,wc,1);
  if (ret != RET_ILUNI) {
    unsigned char c;
    if (ret != 1) abort();
    c = buf[0];
    if (c >= 0xa1 && c <= 0xdf) {
      r[0] = c;
      return 1;
    }
  }

  /* Try JIS X 0208-1990. */
  ret = jisx0208_wctomb(conv,buf,wc,2);
  if (ret != RET_ILUNI) {
    unsigned char c1, c2;
    if (ret != 2) abort();
    if (n < 2)
      return RET_TOOSMALL;
    c1 = buf[0];
    c2 = buf[1];
    if ((c1 >= 0x21 && c1 <= 0x74) && (c2 >= 0x21 && c2 <= 0x7e)) {
      unsigned char t1 = (c1 - 0x21) >> 1;
      unsigned char t2 = (((c1 - 0x21) & 1) ? 0x5e : 0) + (c2 - 0x21);
      r[0] = (t1 < 0x1f ? t1+0x81 : t1+0xc1);
      r[1] = (t2 < 0x3f ? t2+0x40 : t2+0x41);
      return 2;
    }
  }

  /* Try CP932 extensions. */
  ret = cp932ext_wctomb(conv,buf,wc,2);
  if (ret != RET_ILUNI) {
    if (ret != 2) abort();
    if (n < 2)
      return RET_TOOSMALL;
    r[0] = buf[0];
    r[1] = buf[1];
    return 2;
  }

  /* User-defined range. See
   * Ken Lunde's "CJKV Information Processing", table 4-66, p. 206. */
  if (wc >= 0xe000 && wc < 0xe758) {
    unsigned char c1, c2;
    if (n < 2)
      return RET_TOOSMALL;
    c1 = (unsigned int) (wc - 0xe000) / 188;
    c2 = (unsigned int) (wc - 0xe000) % 188;
    r[0] = c1+0xf0;
    r[1] = (c2 < 0x3f ? c2+0x40 : c2+0x41);
    return 2;
  }

  /* Irreversible mappings.  */
  if (wc == 0xff5e) {
    if (n < 2)
      return RET_TOOSMALL;
    r[0] = 0x81;
    r[1] = 0x60;
    return 2;
  }
  if (wc == 0x2225) {
    if (n < 2)
      return RET_TOOSMALL;
    r[0] = 0x81;
    r[1] = 0x61;
    return 2;
  }
  if (wc == 0xff0d) {
    if (n < 2)
      return RET_TOOSMALL;
    r[0] = 0x81;
    r[1] = 0x7c;
    return 2;
  }
  if (wc == 0xffe0) {
    if (n < 2)
      return RET_TOOSMALL;
    r[0] = 0x81;
    r[1] = 0x91;
    return 2;
  }
  if (wc == 0xffe1) {
    if (n < 2)
      return RET_TOOSMALL;
    r[0] = 0x81;
    r[1] = 0x92;
    return 2;
  }

  return RET_ILUNI;
}