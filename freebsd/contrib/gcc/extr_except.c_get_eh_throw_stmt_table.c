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
struct function {TYPE_1__* eh; } ;
typedef  int /*<<< orphan*/  htab_t ;
struct TYPE_2__ {int /*<<< orphan*/  throw_stmt_table; } ;

/* Variables and functions */

htab_t
get_eh_throw_stmt_table (struct function *fun)
{
  return fun->eh->throw_stmt_table;
}