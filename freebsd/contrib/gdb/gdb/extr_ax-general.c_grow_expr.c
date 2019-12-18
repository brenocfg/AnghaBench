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
struct agent_expr {int len; int size; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  xrealloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
grow_expr (struct agent_expr *x, int n)
{
  if (x->len + n > x->size)
    {
      x->size *= 2;
      if (x->size < x->len + n)
	x->size = x->len + n + 10;
      x->buf = xrealloc (x->buf, x->size);
    }
}