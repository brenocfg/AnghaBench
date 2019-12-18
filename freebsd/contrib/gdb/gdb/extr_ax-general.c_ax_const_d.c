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
struct agent_expr {int dummy; } ;
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 

void
ax_const_d (struct agent_expr *x, LONGEST d)
{
  /* FIXME: floating-point support not present yet.  */
  error ("GDB bug: ax-general.c (ax_const_d): floating point not supported yet");
}