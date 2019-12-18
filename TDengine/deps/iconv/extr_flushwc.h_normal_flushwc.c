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
typedef  scalar_t__ ucs4_t ;
typedef  TYPE_1__* conv_t ;
struct TYPE_3__ {scalar_t__ istate; } ;

/* Variables and functions */

__attribute__((used)) static int
normal_flushwc (conv_t conv, ucs4_t *pwc)
{
  ucs4_t last_wc = conv->istate;
  if (last_wc) {
    /* Output the buffered character. */
    conv->istate = 0;
    *pwc = (ucs4_t) last_wc;
    return 1;
  } else
    return 0;
}