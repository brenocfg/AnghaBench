#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union etree_union {int dummy; } etree_union ;
struct TYPE_3__ {int type; union etree_union* exp; } ;
typedef  TYPE_1__ lang_data_statement_type ;

/* Variables and functions */
 int /*<<< orphan*/  lang_data_statement ; 
 TYPE_1__* new_stat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat_ptr ; 

void
lang_add_data (int type, union etree_union *exp)
{
  lang_data_statement_type *new;

  new = new_stat (lang_data_statement, stat_ptr);
  new->exp = exp;
  new->type = type;
}