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
typedef  int /*<<< orphan*/  htab_del ;
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  automaton_decl_eq_p ; 
 int /*<<< orphan*/  automaton_decl_hash ; 
 int /*<<< orphan*/  automaton_decl_table ; 
 int /*<<< orphan*/  dm_automaton ; 
 int /*<<< orphan*/  htab_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ work_automaton_decl ; 

__attribute__((used)) static void
initiate_automaton_decl_table (void)
{
  work_automaton_decl.mode = dm_automaton;
  automaton_decl_table = htab_create (10, automaton_decl_hash,
				      automaton_decl_eq_p, (htab_del) 0);
}