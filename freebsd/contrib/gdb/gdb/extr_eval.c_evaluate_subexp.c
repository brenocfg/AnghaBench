#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct value {int dummy; } ;
struct type {int dummy; } ;
struct expression {TYPE_2__* language_defn; } ;
typedef  enum noside { ____Placeholder_noside } noside ;
struct TYPE_4__ {TYPE_1__* la_exp_desc; } ;
struct TYPE_3__ {struct value* (* evaluate_exp ) (struct type*,struct expression*,int*,int) ;} ;

/* Variables and functions */
 struct value* stub1 (struct type*,struct expression*,int*,int) ; 

__attribute__((used)) static struct value *
evaluate_subexp (struct type *expect_type, struct expression *exp,
		 int *pos, enum noside noside)
{
  return (*exp->language_defn->la_exp_desc->evaluate_exp) 
    (expect_type, exp, pos, noside);
}