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
 int ascii_wctomb (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int cns11643_wctomb (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
euc_tw_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, int n)
{
  unsigned char buf[3];
  int ret;

  /* Code set 0 (ASCII) */
  ret = ascii_wctomb(conv,r,wc,n);
  if (ret != RET_ILUNI)
    return ret;

  ret = cns11643_wctomb(conv,buf,wc,3);
  if (ret != RET_ILUNI) {
    if (ret != 3) abort();

    /* Code set 1 (CNS 11643-1992 Plane 1) */
    if (buf[0] == 1) {
      if (n < 2)
        return RET_TOOSMALL;
      r[0] = buf[1]+0x80;
      r[1] = buf[2]+0x80;
      return 2;
    }

    /* Code set 2 (CNS 11643-1992 Planes 1-16) */
    if (n < 4)
      return RET_TOOSMALL;
    r[0] = 0x8e;
    r[1] = buf[0]+0xa0;
    r[2] = buf[1]+0x80;
    r[3] = buf[2]+0x80;
    return 4;
  }

  return RET_ILUNI;
}