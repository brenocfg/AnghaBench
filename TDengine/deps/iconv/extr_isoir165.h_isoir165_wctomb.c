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
 int RET_ILUNI ; 
 int RET_TOOSMALL ; 
 int /*<<< orphan*/  abort () ; 
 int gb2312_wctomb (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int iso646_cn_wctomb (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int isoir165ext_wctomb (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
isoir165_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, int n)
{
  unsigned char buf[2];
  int ret;

  /* Try the Unicode -> GB2312 table. */
  ret = gb2312_wctomb(conv,buf,wc,2);
  if (ret != RET_ILUNI) {
    if (ret != 2) abort();
    if (!(buf[0] == 0x28 && buf[1] >= 0x21 && buf[1] <= 0x40)) {
      if (n >= 2) {
        r[0] = buf[0];
        r[1] = buf[1];
        return 2;
      }
      return RET_TOOSMALL;
    }
  }
  /* Row 0x2A is GB_1988-80. */
  ret = iso646_cn_wctomb(conv,buf,wc,1);
  if (ret != RET_ILUNI) {
    if (ret != 1) abort();
    if (buf[0] >= 0x21 && buf[0] < 0x7f) {
      if (n >= 2) {
        r[0] = 0x2a;
        r[1] = buf[0];
        return 2;
      }
      return RET_TOOSMALL;
    }
  }
  /* Try the Unicode -> ISO-IR-165 extensions table. */
  ret = isoir165ext_wctomb(conv,r,wc,n);
  return ret;
}