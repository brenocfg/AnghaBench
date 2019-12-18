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
struct agent_expr {int len; int* buf; } ;
typedef  int LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 

__attribute__((used)) static LONGEST
read_const (struct agent_expr *x, int o, int n)
{
  int i;
  LONGEST accum = 0;

  /* Make sure we're not reading off the end of the expression.  */
  if (o + n > x->len)
    error ("GDB bug: ax-general.c (read_const): incomplete constant");

  for (i = 0; i < n; i++)
    accum = (accum << 8) | x->buf[o + i];

  return accum;
}