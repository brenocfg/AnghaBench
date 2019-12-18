#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int ucs4_t ;
typedef  int state_t ;
typedef  TYPE_1__* conv_t ;
struct TYPE_3__ {int ostate; } ;

/* Variables and functions */
 int RET_ILUNI ; 
 int RET_TOOSMALL ; 
 scalar_t__ UTF7_ENCODE_OPTIONAL_CHARS ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ isdirect (unsigned int) ; 
 scalar_t__ isxbase64 (unsigned int) ; 
 scalar_t__ isxdirect (unsigned int) ; 

__attribute__((used)) static int
utf7_wctomb (conv_t conv, unsigned char *r, ucs4_t iwc, int n)
{
  state_t state = conv->ostate;
  unsigned int wc = iwc;
  int count = 0;
  if (state & 3)
    goto active;

/*inactive:*/
  {
    if (UTF7_ENCODE_OPTIONAL_CHARS ? isdirect(wc) : isxdirect(wc)) {
      r[0] = (unsigned char) wc;
      /*conv->ostate = state;*/
      return 1;
    } else {
      *r++ = '+';
      if (wc == '+') {
        if (n < 2)
          return RET_TOOSMALL;
        *r = '-';
        /*conv->ostate = state;*/
        return 2;
      }
      count = 1;
      state = 1;
      goto active;
    }
  }

active:
  {
    /* base64 encoding active */
    if (UTF7_ENCODE_OPTIONAL_CHARS ? isdirect(wc) : isxdirect(wc)) {
      /* deactivate base64 encoding */
      count += ((state & 3) >= 2 ? 1 : 0) + (isxbase64(wc) ? 1 : 0) + 1;
      if (n < count)
        return RET_TOOSMALL;
      if ((state & 3) >= 2) {
        unsigned int i = state & -4;
        unsigned char c;
        if (i < 26)
          c = i+'A';
        else if (i < 52)
          c = i-26+'a';
        else if (i < 62)
          c = i-52+'0';
        else if (i == 62)
          c = '+';
        else if (i == 63)
          c = '/';
        else
          abort();
        *r++ = c;
      }
      if (isxbase64(wc))
        *r++ = '-';
      state = 0;
      *r++ = (unsigned char) wc;
      conv->ostate = state;
      return count;
    } else {
      unsigned int k; /* number of payload bytes to write */
      if (wc < 0x10000) {
        k = 2;
        count += ((state & 3) >= 2 ? 3 : 2);
      } else if (wc < 0x110000) {
        unsigned int wc1 = 0xd800 + ((wc - 0x10000) >> 10);
        unsigned int wc2 = 0xdc00 + ((wc - 0x10000) & 0x3ff);
        wc = (wc1 << 16) | wc2;
        k = 4;
        count += ((state & 3) >= 3 ? 6 : 5);
      } else
        return RET_ILUNI;
      if (n < count)
        return RET_TOOSMALL;
      for (;;) {
        unsigned int i;
        unsigned char c;
        switch (state & 3) {
          case 0: /* inside base64, 6 bits known for 4th byte */
            c = (state & -4) >> 2; state = 1; break;
          case 1: /* inside base64, no pending bits */
            i = (wc >> (8 * --k)) & 0xff;
            c = i >> 2; state = ((i & 3) << 4) | 2; break;
          case 2: /* inside base64, 2 bits known for 2nd byte */
            i = (wc >> (8 * --k)) & 0xff;
            c = (state & -4) | (i >> 4); state = ((i & 15) << 2) | 3; break;
          case 3: /* inside base64, 4 bits known for 3rd byte */
            i = (wc >> (8 * --k)) & 0xff;
            c = (state & -4) | (i >> 6); state = ((i & 63) << 2) | 0; break;
          default: abort(); /* stupid gcc */
        }
        if (c < 26)
          c = c+'A';
        else if (c < 52)
          c = c-26+'a';
        else if (c < 62)
          c = c-52+'0';
        else if (c == 62)
          c = '+';
        else if (c == 63)
          c = '/';
        else
          abort();
        *r++ = c;
        if ((state & 3) && (k == 0))
          break;
      }
      conv->ostate = state;
      return count;
    }
  }
}