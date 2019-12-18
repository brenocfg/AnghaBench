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
typedef  int ucs4_t ;
typedef  int state_t ;
typedef  TYPE_1__* conv_t ;
struct TYPE_3__ {int istate; } ;

/* Variables and functions */
 int RET_SHIFT_ILSEQ (int) ; 
 int RET_TOOFEW (int) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ isxdirect (unsigned char) ; 

__attribute__((used)) static int
utf7_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  state_t state = conv->istate;
  int count = 0; /* number of input bytes already read */
  if (state & 3)
    goto active;
  else
    goto inactive;

inactive:
  {
    /* Here (state & 3) == 0 */
    if (n < count+1)
      goto none;
    {
      unsigned char c = *s;
      if (isxdirect(c)) {
        *pwc = (ucs4_t) c;
        conv->istate = state;
        return count+1;
      }
      if (c == '+') {
        if (n < count+2)
          goto none;
        if (s[1] == '-') {
          *pwc = (ucs4_t) '+';
          conv->istate = state;
          return count+2;
        }
        s++; count++;
        state = 1;
        goto active;
      }
      goto ilseq;
    }
  }

active:
  {
    /* base64 encoding active */
    unsigned int wc = 0;
    state_t base64state = state;
    unsigned int kmax = 2; /* number of payload bytes to read */
    unsigned int k = 0; /* number of payload bytes already read */
    unsigned int base64count = 0; /* number of base64 bytes already read */
    for (;;) {
      unsigned char c = *s;
      unsigned int i;
      if (c >= 'A' && c <= 'Z')
        i = c-'A';
      else if (c >= 'a' && c <= 'z')
        i = c-'a'+26;
      else if (c >= '0' && c <= '9')
        i = c-'0'+52;
      else if (c == '+')
        i = 62;
      else if (c == '/')
        i = 63;
      else {
        /* c terminates base64 encoding */
        if (base64state & -4)
          goto ilseq; /* data must be 0, otherwise illegal */
        if (base64count)
          goto ilseq; /* partial UTF-16 characters are invalid */
        if (c == '-') {
          s++; count++;
        }
        state = 0;
        goto inactive;
      }
      s++; base64count++;
      /* read 6 bits: 0 <= i < 64 */
      switch (base64state & 3) {
        case 1: /* inside base64, no pending bits */
          base64state = (i << 2) | 0; break;
        case 0: /* inside base64, 6 bits remain from 1st byte */
          wc = (wc << 8) | (base64state & -4) | (i >> 4); k++;
          base64state = ((i & 15) << 4) | 2; break;
        case 2: /* inside base64, 4 bits remain from 2nd byte */
          wc = (wc << 8) | (base64state & -4) | (i >> 2); k++;
          base64state = ((i & 3) << 6) | 3; break;
        case 3: /* inside base64, 2 bits remain from 3rd byte */
          wc = (wc << 8) | (base64state & -4) | i; k++;
          base64state = 1; break;
      }
      if (k == kmax) {
        /* UTF-16: When we see a High Surrogate, we must also decode
           the following Low Surrogate. */
        if (kmax == 2 && (wc >= 0xd800 && wc < 0xdc00))
          kmax = 4;
        else
          break;
      }
      if (n < count+base64count+1)
        goto none;
    }
    /* Here k = kmax > 0, hence base64count > 0. */
    if ((base64state & 3) == 0) abort();
    if (kmax == 4) {
      ucs4_t wc1 = wc >> 16;
      ucs4_t wc2 = wc & 0xffff;
      if (!(wc1 >= 0xd800 && wc1 < 0xdc00)) abort();
      if (!(wc2 >= 0xdc00 && wc2 < 0xe000)) goto ilseq;
      *pwc = 0x10000 + ((wc1 - 0xd800) << 10) + (wc2 - 0xdc00);
    } else {
      *pwc = wc;
    }
    conv->istate = base64state;
    return count+base64count;
  }

none:
  conv->istate = state;
  return RET_TOOFEW(count);

ilseq:
  conv->istate = state;
  return RET_SHIFT_ILSEQ(count);
}