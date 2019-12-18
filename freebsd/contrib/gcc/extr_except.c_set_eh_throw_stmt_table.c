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
struct htab {int dummy; } ;
struct function {TYPE_1__* eh; } ;
struct TYPE_2__ {struct htab* throw_stmt_table; } ;

/* Variables and functions */

void
set_eh_throw_stmt_table (struct function *fun, struct htab *table)
{
  fun->eh->throw_stmt_table = table;
}