#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * exp; } ;
typedef  TYPE_1__ lang_assignment_statement_type ;
typedef  int /*<<< orphan*/  etree_type ;

/* Variables and functions */
 int /*<<< orphan*/  lang_assignment_statement ; 
 TYPE_1__* new_stat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat_ptr ; 

lang_assignment_statement_type *
lang_add_assignment (etree_type *exp)
{
  lang_assignment_statement_type *new;

  new = new_stat (lang_assignment_statement, stat_ptr);
  new->exp = exp;
  return new;
}