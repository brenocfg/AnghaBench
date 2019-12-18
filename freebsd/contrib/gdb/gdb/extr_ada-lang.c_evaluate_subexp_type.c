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
struct value {int dummy; } ;
struct expression {TYPE_1__* language_defn; } ;
struct TYPE_2__ {struct value* (* evaluate_exp ) (int /*<<< orphan*/ ,struct expression*,int*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EVAL_AVOID_SIDE_EFFECTS ; 
 int /*<<< orphan*/  NULL_TYPE ; 
 struct value* stub1 (int /*<<< orphan*/ ,struct expression*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct value *
evaluate_subexp_type (struct expression *exp, int *pos)
{
  return (*exp->language_defn->evaluate_exp)
    (NULL_TYPE, exp, pos, EVAL_AVOID_SIDE_EFFECTS);
}