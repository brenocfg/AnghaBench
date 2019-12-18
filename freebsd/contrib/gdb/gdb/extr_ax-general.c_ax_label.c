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
struct agent_expr {int* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 

void
ax_label (struct agent_expr *x, int patch, int target)
{
  /* Make sure the value is in range.  Don't accept 0xffff as an
     offset; that's our magic sentinel value for unpatched branches.  */
  if (target < 0 || target >= 0xffff)
    error ("GDB bug: ax-general.c (ax_label): label target out of range");

  x->buf[patch] = (target >> 8) & 0xff;
  x->buf[patch + 1] = target & 0xff;
}