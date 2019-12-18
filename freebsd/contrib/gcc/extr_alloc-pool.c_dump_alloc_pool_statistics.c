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
struct output_info {int count; int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_pool_hash ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  htab_traverse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct output_info*) ; 
 int /*<<< orphan*/  print_statistics ; 
 int /*<<< orphan*/  stderr ; 

void
dump_alloc_pool_statistics (void)
{
#ifdef GATHER_STATISTICS
  struct output_info info;

  if (!alloc_pool_hash)
    return;

  fprintf (stderr, "\nAlloc-pool Kind        Pools  Allocated      Peak        Leak\n");
  fprintf (stderr, "-------------------------------------------------------------\n");
  info.count = 0;
  info.size = 0;
  htab_traverse (alloc_pool_hash, print_statistics, &info);
  fprintf (stderr, "-------------------------------------------------------------\n");
  fprintf (stderr, "%-20s %7d %10d\n",
	   "Total", info.count, info.size);
  fprintf (stderr, "-------------------------------------------------------------\n");
#endif
}