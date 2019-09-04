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
typedef  TYPE_1__* conv_t ;
struct TYPE_3__ {unsigned char ostate; } ;

/* Variables and functions */
 int RET_TOOSMALL ; 

__attribute__((used)) static int
big5hkscs1999_reset (conv_t conv, unsigned char *r, size_t n)
{
  unsigned char last = conv->ostate;

  if (last) {
    if (n < 2)
      return RET_TOOSMALL;
    r[0] = 0x88;
    r[1] = last;
    /* conv->ostate = 0; will be done by the caller */
    return 2;
  } else
    return 0;
}