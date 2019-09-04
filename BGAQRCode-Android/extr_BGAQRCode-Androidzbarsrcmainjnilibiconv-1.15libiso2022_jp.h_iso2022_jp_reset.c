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
typedef  scalar_t__ state_t ;
typedef  TYPE_1__* conv_t ;
struct TYPE_3__ {scalar_t__ ostate; } ;

/* Variables and functions */
 unsigned char ESC ; 
 int RET_TOOSMALL ; 
 scalar_t__ STATE_ASCII ; 

__attribute__((used)) static int
iso2022_jp_reset (conv_t conv, unsigned char *r, size_t n)
{
  state_t state = conv->ostate;
  if (state != STATE_ASCII) {
    if (n < 3)
      return RET_TOOSMALL;
    r[0] = ESC;
    r[1] = '(';
    r[2] = 'B';
    /* conv->ostate = 0; will be done by the caller */
    return 3;
  } else
    return 0;
}