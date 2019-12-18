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
typedef  int /*<<< orphan*/  symbolS ;
typedef  int /*<<< orphan*/  expressionS ;

/* Variables and functions */
 int /*<<< orphan*/  current_location (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_expr_symbol (int /*<<< orphan*/ *) ; 

symbolS *
expr_build_dot (void)
{
  expressionS e;

  current_location (&e);
  return make_expr_symbol (&e);
}