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
struct TYPE_3__ {int /*<<< orphan*/ * fill; } ;
typedef  TYPE_1__ lang_fill_statement_type ;
typedef  int /*<<< orphan*/  fill_type ;

/* Variables and functions */
 int /*<<< orphan*/  lang_fill_statement ; 
 TYPE_1__* new_stat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat_ptr ; 

void
lang_add_fill (fill_type *fill)
{
  lang_fill_statement_type *new;

  new = new_stat (lang_fill_statement, stat_ptr);
  new->fill = fill;
}