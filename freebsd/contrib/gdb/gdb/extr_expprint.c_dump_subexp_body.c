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
struct ui_file {int dummy; } ;
struct expression {TYPE_2__* language_defn; } ;
struct TYPE_4__ {TYPE_1__* la_exp_desc; } ;
struct TYPE_3__ {int (* dump_subexp_body ) (struct expression*,struct ui_file*,int) ;} ;

/* Variables and functions */
 int stub1 (struct expression*,struct ui_file*,int) ; 

__attribute__((used)) static int
dump_subexp_body (struct expression *exp, struct ui_file *stream, int elt)
{
  return exp->language_defn->la_exp_desc->dump_subexp_body (exp, stream, elt);
}