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
typedef  int /*<<< orphan*/  state_t ;
typedef  TYPE_1__* conv_t ;
struct TYPE_3__ {int /*<<< orphan*/  ostate; } ;

/* Variables and functions */
 int RET_TOOSMALL ; 
 unsigned char SI ; 
 int /*<<< orphan*/  SPLIT_STATE ; 
 scalar_t__ STATE_ASCII ; 
 scalar_t__ state1 ; 
 int /*<<< orphan*/  state2 ; 

__attribute__((used)) static int
iso2022_kr_reset (conv_t conv, unsigned char *r, size_t n)
{
  state_t state = conv->ostate;
  SPLIT_STATE;
  (void)state2;
  if (state1 != STATE_ASCII) {
    if (n < 1)
      return RET_TOOSMALL;
    r[0] = SI;
    /* conv->ostate = 0; will be done by the caller */
    return 1;
  } else
    return 0;
}