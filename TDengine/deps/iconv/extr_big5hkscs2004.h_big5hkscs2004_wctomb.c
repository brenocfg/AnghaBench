#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ucs4_t ;
typedef  TYPE_1__* conv_t ;
struct TYPE_7__ {unsigned char ostate; } ;

/* Variables and functions */
 int RET_ILUNI ; 
 int RET_TOOSMALL ; 
 int /*<<< orphan*/  abort () ; 
 int big5_wctomb (TYPE_1__*,unsigned char*,int,int) ; 
 int hkscs1999_wctomb (TYPE_1__*,unsigned char*,int,int) ; 
 int hkscs2001_wctomb (TYPE_1__*,unsigned char*,int,int) ; 
 int hkscs2004_wctomb (TYPE_1__*,unsigned char*,int,int) ; 

__attribute__((used)) static int
big5hkscs2004_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, int n)
{
  int count = 0;
  unsigned char last = conv->ostate;

  if (last) {
    /* last is = 0x66 or = 0xa7. */
    if (wc == 0x0304 || wc == 0x030c) {
      /* Output the combined character. */
      if (n >= 2) {
        r[0] = 0x88;
        r[1] = last + ((wc & 24) >> 2) - 4; /* = 0x62 or 0x64 or 0xa3 or 0xa5 */
        conv->ostate = 0;
        return 2;
      } else
        return RET_TOOSMALL;
    }

    /* Output the buffered character. */
    if (n < 2)
      return RET_TOOSMALL;
    r[0] = 0x88;
    r[1] = last;
    r += 2;
    count = 2;
  }

  /* Code set 0 (ASCII) */
  if (wc < 0x0080) {
    /* Plain ASCII character. */
    if (n > count) {
      r[0] = (unsigned char) wc;
      conv->ostate = 0;
      return count+1;
    } else
      return RET_TOOSMALL;
  } else {
    unsigned char buf[2];
    int ret;

    /* Code set 1 (BIG5 extended) */
    ret = big5_wctomb(conv,buf,wc,2);
    if (ret != RET_ILUNI) {
      if (ret != 2) abort();
      if (!((buf[0] == 0xc6 && buf[1] >= 0xa1) || buf[0] == 0xc7)) {
        if (n >= count+2) {
          r[0] = buf[0];
          r[1] = buf[1];
          conv->ostate = 0;
          return count+2;
        } else
          return RET_TOOSMALL;
      }
    }
    ret = hkscs1999_wctomb(conv,buf,wc,2);
    if (ret != RET_ILUNI) {
      if (ret != 2) abort();
      if ((wc & ~0x0020) == 0x00ca) {
        /* A possible first character of a multi-character sequence. We have to
           buffer it. */
        if (!(buf[0] == 0x88 && (buf[1] == 0x66 || buf[1] == 0xa7))) abort();
        conv->ostate = buf[1]; /* = 0x66 or = 0xa7 */
        return count+0;
      }
      if (n >= count+2) {
        r[0] = buf[0];
        r[1] = buf[1];
        conv->ostate = 0;
        return count+2;
      } else
        return RET_TOOSMALL;
    }
    ret = hkscs2001_wctomb(conv,buf,wc,2);
    if (ret != RET_ILUNI) {
      if (ret != 2) abort();
      if (n >= count+2) {
        r[0] = buf[0];
        r[1] = buf[1];
        conv->ostate = 0;
        return count+2;
      } else
        return RET_TOOSMALL;
    }
    ret = hkscs2004_wctomb(conv,buf,wc,2);
    if (ret != RET_ILUNI) {
      if (ret != 2) abort();
      if (n >= count+2) {
        r[0] = buf[0];
        r[1] = buf[1];
        conv->ostate = 0;
        return count+2;
      } else
        return RET_TOOSMALL;
    }
    return RET_ILUNI;
  }
}