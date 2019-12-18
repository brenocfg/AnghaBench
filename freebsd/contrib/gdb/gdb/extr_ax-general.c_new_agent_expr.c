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
struct agent_expr {int size; int /*<<< orphan*/  scope; void* buf; scalar_t__ len; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 void* xmalloc (int) ; 

struct agent_expr *
new_agent_expr (CORE_ADDR scope)
{
  struct agent_expr *x = xmalloc (sizeof (*x));
  x->len = 0;
  x->size = 1;			/* Change this to a larger value once
				   reallocation code is tested.  */
  x->buf = xmalloc (x->size);
  x->scope = scope;

  return x;
}