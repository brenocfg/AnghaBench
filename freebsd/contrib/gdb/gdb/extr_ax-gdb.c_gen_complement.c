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
struct axs_value {int /*<<< orphan*/  type; } ;
struct agent_expr {int dummy; } ;

/* Variables and functions */
 scalar_t__ TYPE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_CODE_INT ; 
 int /*<<< orphan*/  aop_bit_not ; 
 int /*<<< orphan*/  ax_simple (struct agent_expr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  gen_extend (struct agent_expr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_integral_promotions (struct agent_expr*,struct axs_value*) ; 
 int /*<<< orphan*/  gen_usual_unary (struct agent_expr*,struct axs_value*) ; 

__attribute__((used)) static void
gen_complement (struct agent_expr *ax, struct axs_value *value)
{
  if (TYPE_CODE (value->type) != TYPE_CODE_INT)
    error ("Illegal type of operand to `~'.");

  gen_usual_unary (ax, value);
  gen_integral_promotions (ax, value);
  ax_simple (ax, aop_bit_not);
  gen_extend (ax, value->type);
}