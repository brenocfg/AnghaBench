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
 int ascii_mbtowc (int /*<<< orphan*/ ,int*,unsigned char const*,int) ; 
 int ksc5601_mbtowc (int /*<<< orphan*/ ,int*,unsigned char*,int) ; 
 int uhc_1_mbtowc (int /*<<< orphan*/ ,int*,unsigned char const*,int) ; 
 int uhc_2_mbtowc (int /*<<< orphan*/ ,int*,unsigned char const*,int) ; 

__attribute__((used)) static int
cp949_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  unsigned char c = *s;
  /* Code set 0 (ASCII) */
  if (c < 0x80)
    return ascii_mbtowc(conv,pwc,s,n);
  /* UHC part 1 */
  if (c >= 0x81 && c <= 0xa0)
    return uhc_1_mbtowc(conv,pwc,s,n);
  if (c >= 0xa1 && c < 0xff) {
    if (n < 2)
      return RET_TOOFEW(0);
    {
      unsigned char c2 = s[1];
      if (c2 < 0xa1)
        /* UHC part 2 */
        return uhc_2_mbtowc(conv,pwc,s,n);
      else if (c2 < 0xff && !(c == 0xa2 && c2 == 0xe8)) {
        /* Code set 1 (KS C 5601-1992, now KS X 1001:1998) */
        unsigned char buf[2];
        int ret;
        buf[0] = c-0x80; buf[1] = c2-0x80;
        ret = ksc5601_mbtowc(conv,pwc,buf,2);
        if (ret != RET_ILSEQ)
          return ret;
        /* User-defined characters */
        if (c == 0xc9) {
          *pwc = 0xe000 + (c2 - 0xa1);
          return 2;
        }
        if (c == 0xfe) {
          *pwc = 0xe05e + (c2 - 0xa1);
          return 2;
        }
      }
    }
  }
  return RET_ILSEQ;
}