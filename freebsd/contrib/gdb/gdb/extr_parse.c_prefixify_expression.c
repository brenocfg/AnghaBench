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
struct expression {int nelts; } ;

/* Variables and functions */
 int EXP_ELEM_TO_BYTES (int) ; 
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  memcpy (struct expression*,struct expression*,int) ; 
 int /*<<< orphan*/  prefixify_subexp (struct expression*,struct expression*,int,int) ; 

__attribute__((used)) static void
prefixify_expression (struct expression *expr)
{
  int len =
  sizeof (struct expression) + EXP_ELEM_TO_BYTES (expr->nelts);
  struct expression *temp;
  int inpos = expr->nelts, outpos = 0;

  temp = (struct expression *) alloca (len);

  /* Copy the original expression into temp.  */
  memcpy (temp, expr, len);

  prefixify_subexp (temp, expr, inpos, outpos);
}