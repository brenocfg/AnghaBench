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
struct type {int dummy; } ;
struct expression {TYPE_1__* language_defn; } ;
typedef  enum noside { ____Placeholder_noside } noside ;
struct TYPE_2__ {struct value* (* evaluate_exp ) (struct type*,struct expression*,int*,int) ;} ;

/* Variables and functions */
 struct value* stub1 (struct type*,struct expression*,int*,int) ; 

__attribute__((used)) static struct value *
evaluate_subexp (struct type *expect_type, struct expression *exp, int *pos,
		 enum noside noside)
{
  return (*exp->language_defn->evaluate_exp) (expect_type, exp, pos, noside);
}