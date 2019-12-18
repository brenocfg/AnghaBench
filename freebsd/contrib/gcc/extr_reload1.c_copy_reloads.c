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
struct reload {int dummy; } ;
struct insn_chain {int n_reloads; void* rld; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int n_reloads ; 
 void* obstack_alloc (int /*<<< orphan*/ *,int) ; 
 void* reload_insn_firstobj ; 
 int /*<<< orphan*/  reload_obstack ; 
 int /*<<< orphan*/  rld ; 

__attribute__((used)) static void
copy_reloads (struct insn_chain *chain)
{
  chain->n_reloads = n_reloads;
  chain->rld = obstack_alloc (&reload_obstack,
			      n_reloads * sizeof (struct reload));
  memcpy (chain->rld, rld, n_reloads * sizeof (struct reload));
  reload_insn_firstobj = obstack_alloc (&reload_obstack, 0);
}