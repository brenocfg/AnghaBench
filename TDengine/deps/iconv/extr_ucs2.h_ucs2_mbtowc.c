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

__attribute__((used)) static int
ucs2_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  state_t state = conv->istate;
  int count = 0;
  for (; n >= 2;) {
    ucs4_t wc = (state ? s[0] + (s[1] << 8) : (s[0] << 8) + s[1]);
    s += 2; n -= 2; count += 2;
    if (wc == 0xfeff) {
    } else if (wc == 0xfffe) {
      state ^= 1;
    } else if (wc >= 0xd800 && wc < 0xe000) {
      conv->istate = state;
      return RET_SHIFT_ILSEQ(count);
    } else {
      *pwc = wc;
      conv->istate = state;
      return count;
    }
  }
  conv->istate = state;
  return RET_TOOFEW(count);
}