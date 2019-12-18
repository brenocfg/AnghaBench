#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ X_op; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 scalar_t__ O_max ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  expr_set_precedence () ; 

void
expr_begin (void)
{
  expr_set_precedence ();

  /* Verify that X_op field is wide enough.  */
  {
    expressionS e;
    e.X_op = O_max;
    assert (e.X_op == O_max);
  }
}