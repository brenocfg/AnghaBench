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
struct TYPE_3__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 TYPE_1__* current_inferior ; 
 int /*<<< orphan*/  gdb_assert (TYPE_1__*) ; 
 int /*<<< orphan*/  terminal_init_inferior_with_pgrp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gnu_terminal_init_inferior (void)
{
  gdb_assert (current_inferior);
  terminal_init_inferior_with_pgrp (current_inferior->pid);
}