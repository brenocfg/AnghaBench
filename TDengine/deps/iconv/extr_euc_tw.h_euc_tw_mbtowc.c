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
 int ascii_mbtowc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int cns11643_15_mbtowc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,int) ; 
 int cns11643_1_mbtowc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,int) ; 
 int cns11643_2_mbtowc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,int) ; 
 int cns11643_3_mbtowc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,int) ; 
 int cns11643_4_mbtowc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,int) ; 
 int cns11643_5_mbtowc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,int) ; 
 int cns11643_6_mbtowc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,int) ; 
 int cns11643_7_mbtowc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static int
euc_tw_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  unsigned char c = *s;
  /* Code set 0 (ASCII) */
  if (c < 0x80)
    return ascii_mbtowc(conv,pwc,s,n);
  /* Code set 1 (CNS 11643-1992 Plane 1) */
  if (c >= 0xa1 && c < 0xff) {
    if (n < 2)
      return RET_TOOFEW(0);
    {
      unsigned char c2 = s[1];
      if (c2 >= 0xa1 && c2 < 0xff) {
        unsigned char buf[2];
        buf[0] = c-0x80; buf[1] = c2-0x80;
        return cns11643_1_mbtowc(conv,pwc,buf,2);
      } else
        return RET_ILSEQ;
    }
  }
  /* Code set 2 (CNS 11643-1992 Planes 1-16) */
  if (c == 0x8e) {
    if (n < 4)
      return RET_TOOFEW(0);
    {
      unsigned char c2 = s[1];
      if (c2 >= 0xa1 && c2 <= 0xb0) {
        unsigned char c3 = s[2];
        unsigned char c4 = s[3];
        if (c3 >= 0xa1 && c3 < 0xff && c4 >= 0xa1 && c4 < 0xff) {
          unsigned char buf[2];
          int ret;
          buf[0] = c3-0x80; buf[1] = c4-0x80;
          switch (c2-0xa0) {
            case 1: ret = cns11643_1_mbtowc(conv,pwc,buf,2); break;
            case 2: ret = cns11643_2_mbtowc(conv,pwc,buf,2); break;
            case 3: ret = cns11643_3_mbtowc(conv,pwc,buf,2); break;
            case 4: ret = cns11643_4_mbtowc(conv,pwc,buf,2); break;
            case 5: ret = cns11643_5_mbtowc(conv,pwc,buf,2); break;
            case 6: ret = cns11643_6_mbtowc(conv,pwc,buf,2); break;
            case 7: ret = cns11643_7_mbtowc(conv,pwc,buf,2); break;
            case 15: ret = cns11643_15_mbtowc(conv,pwc,buf,2); break;
            default: return RET_ILSEQ;
          }
          if (ret == RET_ILSEQ)
            return RET_ILSEQ;
          if (ret != 2) abort();
          return 4;
        }
      }
    }
  }
  return RET_ILSEQ;
}