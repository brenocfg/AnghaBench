#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  automaton_decl_table ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
finish_automaton_decl_table (void)
{
  htab_delete (automaton_decl_table);
}