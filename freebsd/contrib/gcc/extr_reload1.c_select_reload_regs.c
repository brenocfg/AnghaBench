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
struct insn_chain {struct insn_chain* next_need_reload; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_reload_regs (struct insn_chain*) ; 
 struct insn_chain* insns_need_reload ; 

__attribute__((used)) static void
select_reload_regs (void)
{
  struct insn_chain *chain;

  /* Try to satisfy the needs for each insn.  */
  for (chain = insns_need_reload; chain != 0;
       chain = chain->next_need_reload)
    find_reload_regs (chain);
}