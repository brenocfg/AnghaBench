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
typedef  int state_t ;
typedef  TYPE_1__* conv_t ;
struct TYPE_3__ {int ostate; } ;

/* Variables and functions */
 int RET_TOOSMALL ; 
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static int
utf7_reset (conv_t conv, unsigned char *r, int n)
{
  state_t state = conv->ostate;
  if (state & 3) {
    /* deactivate base64 encoding */
    unsigned int count = ((state & 3) >= 2 ? 1 : 0) + 1;
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
    *r++ = '-';
    /* conv->ostate = 0; will be done by the caller */
    return count;
  } else
    return 0;
}