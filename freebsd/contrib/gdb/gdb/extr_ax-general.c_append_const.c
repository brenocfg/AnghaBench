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
struct agent_expr {int* buf; int len; } ;
typedef  int LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  grow_expr (struct agent_expr*,int) ; 

__attribute__((used)) static void
append_const (struct agent_expr *x, LONGEST val, int n)
{
  int i;

  grow_expr (x, n);
  for (i = n - 1; i >= 0; i--)
    {
      x->buf[x->len + i] = val & 0xff;
      val >>= 8;
    }
  x->len += n;
}