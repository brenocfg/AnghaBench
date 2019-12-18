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
typedef  int /*<<< orphan*/  tree ;
typedef  enum lvalue_use { ____Placeholder_lvalue_use } lvalue_use ;

/* Variables and functions */
 int /*<<< orphan*/  lvalue_error (int) ; 
 int lvalue_p (int /*<<< orphan*/ ) ; 

int
lvalue_or_else (tree ref, enum lvalue_use use)
{
  int win = lvalue_p (ref);

  if (!win)
    lvalue_error (use);

  return win;
}