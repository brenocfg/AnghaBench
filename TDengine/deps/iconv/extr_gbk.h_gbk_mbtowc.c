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
 int cp936ext_mbtowc (int /*<<< orphan*/ ,int*,unsigned char*,int) ; 
 int gb2312_mbtowc (int /*<<< orphan*/ ,int*,unsigned char*,int) ; 
 int gbkext1_mbtowc (int /*<<< orphan*/ ,int*,unsigned char const*,int) ; 
 int gbkext2_mbtowc (int /*<<< orphan*/ ,int*,unsigned char const*,int) ; 

__attribute__((used)) static int
gbk_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  unsigned char c = *s;

  if (c >= 0x81 && c < 0xff) {
    if (n < 2)
      return RET_TOOFEW(0);
    if (c >= 0xa1 && c <= 0xf7) {
      unsigned char c2 = s[1];
      if (c == 0xa1) {
        if (c2 == 0xa4) {
          *pwc = 0x00b7;
          return 2;
        }
        if (c2 == 0xaa) {
          *pwc = 0x2014;
          return 2;
        }
      }
      if (c2 >= 0xa1 && c2 < 0xff) {
        unsigned char buf[2];
        int ret;
        buf[0] = c-0x80; buf[1] = c2-0x80;
        ret = gb2312_mbtowc(conv,pwc,buf,2);
        if (ret != RET_ILSEQ)
          return ret;
        buf[0] = c; buf[1] = c2;
        ret = cp936ext_mbtowc(conv,pwc,buf,2);
        if (ret != RET_ILSEQ)
          return ret;
      }
    }
    if (c >= 0x81 && c <= 0xa0)
      return gbkext1_mbtowc(conv,pwc,s,2);
    if (c >= 0xa8 && c <= 0xfe)
      return gbkext2_mbtowc(conv,pwc,s,2);
    if (c == 0xa2) {
      unsigned char c2 = s[1];
      if (c2 >= 0xa1 && c2 <= 0xaa) {
        *pwc = 0x2170+(c2-0xa1);
        return 2;
      }
    }
  }
  return RET_ILSEQ;
}