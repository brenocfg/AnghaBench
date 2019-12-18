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
struct score_got_info {int /*<<< orphan*/ * got_entries; } ;
typedef  int /*<<< orphan*/ * htab_t ;

/* Variables and functions */
 int /*<<< orphan*/  htab_traverse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  score_elf_resolve_final_got_entry ; 

__attribute__((used)) static void
score_elf_resolve_final_got_entries (struct score_got_info *g)
{
  htab_t got_entries;

  do
    {
      got_entries = g->got_entries;

      htab_traverse (got_entries,
		     score_elf_resolve_final_got_entry,
		     &got_entries);
    }
  while (got_entries == NULL);
}