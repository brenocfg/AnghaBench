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
struct frame_unwind_table {int nr; int /*<<< orphan*/ ** sniffer; } ;
typedef  int /*<<< orphan*/  frame_unwind_sniffer_ftype ;

/* Variables and functions */
 int /*<<< orphan*/ ** xrealloc (int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static void
append_predicate (struct frame_unwind_table *table,
		  frame_unwind_sniffer_ftype *sniffer)
{
  table->sniffer = xrealloc (table->sniffer, ((table->nr + 1)
					      * sizeof (frame_unwind_sniffer_ftype *)));
  table->sniffer[table->nr] = sniffer;
  table->nr++;
}