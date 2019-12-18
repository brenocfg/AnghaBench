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
 int /*<<< orphan*/  abort () ; 
 int ascii_mbtowc (int /*<<< orphan*/ ,int*,unsigned char const*,int) ; 
 int jisx0201_mbtowc (int /*<<< orphan*/ ,int*,unsigned char const*,int) ; 
 int jisx0208_mbtowc (int /*<<< orphan*/ ,int*,unsigned char*,int) ; 
 int jisx0212_mbtowc (int /*<<< orphan*/ ,int*,unsigned char*,int) ; 

__attribute__((used)) static int
euc_jp_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  unsigned char c = *s;
  /* Code set 0 (ASCII or JIS X 0201-1976 Roman) */
  if (c < 0x80)
    return ascii_mbtowc(conv,pwc,s,n);
  /* Code set 1 (JIS X 0208) */
  if (c >= 0xa1 && c < 0xff) {
    if (n < 2)
      return RET_TOOFEW(0);
    if (c < 0xf5) {
      unsigned char c2 = s[1];
      if (c2 >= 0xa1 && c2 < 0xff) {
        unsigned char buf[2];
        buf[0] = c-0x80; buf[1] = c2-0x80;
        return jisx0208_mbtowc(conv,pwc,buf,2);
      } else
        return RET_ILSEQ;
    } else {
      /* User-defined range. See
       * Ken Lunde's "CJKV Information Processing", table 4-66, p. 206. */
      unsigned char c2 = s[1];
      if (c2 >= 0xa1 && c2 < 0xff) {
        *pwc = 0xe000 + 94*(c-0xf5) + (c2-0xa1);
        return 2;
      } else
        return RET_ILSEQ;
    }
  }
  /* Code set 2 (half-width katakana) */
  if (c == 0x8e) {
    if (n < 2)
      return RET_TOOFEW(0);
    {
      unsigned char c2 = s[1];
      if (c2 >= 0xa1 && c2 < 0xe0) {
        int ret = jisx0201_mbtowc(conv,pwc,s+1,n-1);
        if (ret == RET_ILSEQ)
          return RET_ILSEQ;
        if (ret != 1) abort();
        return 2;
      } else
        return RET_ILSEQ;
    }
  }
  /* Code set 3 (JIS X 0212-1990) */
  if (c == 0x8f) {
    if (n < 2)
      return RET_TOOFEW(0);
    {
      unsigned char c2 = s[1];
      if (c2 >= 0xa1 && c2 < 0xff) {
        if (n < 3)
          return RET_TOOFEW(0);
        if (c2 < 0xf5) {
          unsigned char c3 = s[2];
          if (c3 >= 0xa1 && c3 < 0xff) {
            unsigned char buf[2];
            int ret;
            buf[0] = c2-0x80; buf[1] = c3-0x80;
            ret = jisx0212_mbtowc(conv,pwc,buf,2);
            if (ret == RET_ILSEQ)
              return RET_ILSEQ;
            if (ret != 2) abort();
            return 3;
          } else
            return RET_ILSEQ;
        } else {
          /* User-defined range. See
           * Ken Lunde's "CJKV Information Processing", table 4-66, p. 206. */
          unsigned char c3 = s[2];
          if (c3 >= 0xa1 && c3 < 0xff) {
            *pwc = 0xe3ac + 94*(c2-0xf5) + (c3-0xa1);
            return 3;
          } else
            return RET_ILSEQ;
        }
      } else
        return RET_ILSEQ;
    }
  }
  return RET_ILSEQ;
}