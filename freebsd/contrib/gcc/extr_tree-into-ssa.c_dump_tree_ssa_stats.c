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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  def_blocks ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  htab_statistics (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
dump_tree_ssa_stats (FILE *file)
{
  fprintf (file, "\nHash table statistics:\n");

  fprintf (file, "    def_blocks: ");
  htab_statistics (file, def_blocks);

  fprintf (file, "\n");
}