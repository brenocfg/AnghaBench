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
typedef  int /*<<< orphan*/  ucs4_t ;
typedef  int /*<<< orphan*/  conv_t ;

/* Variables and functions */
 int RET_ILSEQ ; 
 int RET_TOOFEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int gb2312_mbtowc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int iso646_cn_mbtowc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int isoir165ext_mbtowc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char const*,int) ; 

__attribute__((used)) static int
isoir165_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  int ret;

  /* Map full-width pinyin (row 0x28) like half-width pinyin (row 0x2B). */
  if (s[0] == 0x28) {
    if (n >= 2) {
      unsigned char c2 = s[1];
      if (c2 >= 0x21 && c2 <= 0x40) {
        unsigned char buf[2];
        buf[0] = 0x2b;
        buf[1] = c2;
        ret = isoir165ext_mbtowc(conv,pwc,buf,2);
        if (ret != RET_ILSEQ)
          return ret;
      }
    }
  }
  /* Try the GB2312 -> Unicode table. */
  ret = gb2312_mbtowc(conv,pwc,s,n);
  if (ret != RET_ILSEQ)
    return ret;
  /* Row 0x2A is GB_1988-80. */
  if (s[0] == 0x2a) {
    if (n >= 2) {
      unsigned char c2 = s[1];
      if (c2 >= 0x21 && c2 < 0x7f) {
        int ret = iso646_cn_mbtowc(conv,pwc,s+1,1);
        if (ret != 1) abort();
        return 2;
      }
      return RET_ILSEQ;
    }
    return RET_TOOFEW(0);
  }
  /* Try the ISO-IR-165 extensions -> Unicode table. */
  ret = isoir165ext_mbtowc(conv,pwc,s,n);
  return ret;
}