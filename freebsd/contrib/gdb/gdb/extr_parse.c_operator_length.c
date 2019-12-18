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
struct expression {TYPE_2__* language_defn; } ;
struct TYPE_4__ {TYPE_1__* la_exp_desc; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* operator_length ) (struct expression*,int,int*,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct expression*,int,int*,int*) ; 

void
operator_length (struct expression *expr, int endpos, int *oplenp, int *argsp)
{
  expr->language_defn->la_exp_desc->operator_length (expr, endpos,
						     oplenp, argsp);
}