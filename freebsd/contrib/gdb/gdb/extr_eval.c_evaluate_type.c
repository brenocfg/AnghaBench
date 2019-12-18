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
struct value {int dummy; } ;
struct expression {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVAL_AVOID_SIDE_EFFECTS ; 
 int /*<<< orphan*/  NULL_TYPE ; 
 struct value* evaluate_subexp (int /*<<< orphan*/ ,struct expression*,int*,int /*<<< orphan*/ ) ; 

struct value *
evaluate_type (struct expression *exp)
{
  int pc = 0;
  return evaluate_subexp (NULL_TYPE, exp, &pc, EVAL_AVOID_SIDE_EFFECTS);
}