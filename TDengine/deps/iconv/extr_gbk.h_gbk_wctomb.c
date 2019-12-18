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
 int cp936ext_wctomb (int /*<<< orphan*/ ,unsigned char*,int,int) ; 
 int gb2312_wctomb (int /*<<< orphan*/ ,unsigned char*,int,int) ; 
 int gbkext_inv_wctomb (int /*<<< orphan*/ ,unsigned char*,int,int) ; 

__attribute__((used)) static int
gbk_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, int n)
{
  unsigned char buf[2];
  int ret;

  if (wc != 0x30fb && wc != 0x2015) {
    ret = gb2312_wctomb(conv,buf,wc,2);
    if (ret != RET_ILUNI) {
      if (ret != 2) abort();
      if (n < 2)
        return RET_TOOSMALL;
      r[0] = buf[0]+0x80;
      r[1] = buf[1]+0x80;
      return 2;
    }
  }
  ret = gbkext_inv_wctomb(conv,buf,wc,2);
  if (ret != RET_ILUNI) {
    if (ret != 2) abort();
    if (n < 2)
      return RET_TOOSMALL;
    r[0] = buf[0];
    r[1] = buf[1];
    return 2;
  }
  if (wc >= 0x2170 && wc <= 0x2179) {
    if (n < 2)
      return RET_TOOSMALL;
    r[0] = 0xa2;
    r[1] = 0xa1 + (wc-0x2170);
    return 2;
  }
  ret = cp936ext_wctomb(conv,buf,wc,2);
  if (ret != RET_ILUNI) {
    if (ret != 2) abort();
    if (n < 2)
      return RET_TOOSMALL;
    r[0] = buf[0];
    r[1] = buf[1];
    return 2;
  }
  if (wc == 0x00b7) {
    if (n < 2)
      return RET_TOOSMALL;
    r[0] = 0xa1;
    r[1] = 0xa4;
    return 2;
  }
  if (wc == 0x2014) {
    if (n < 2)
      return RET_TOOSMALL;
    r[0] = 0xa1;
    r[1] = 0xaa;
    return 2;
  }

  return RET_ILUNI;
}