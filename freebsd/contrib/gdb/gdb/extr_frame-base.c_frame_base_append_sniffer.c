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
struct gdbarch {int dummy; } ;
struct frame_base_table {int dummy; } ;
typedef  int /*<<< orphan*/  frame_base_sniffer_ftype ;

/* Variables and functions */
 int /*<<< orphan*/  append_predicate (struct frame_base_table*,int /*<<< orphan*/ *) ; 
 struct frame_base_table* frame_base_table (struct gdbarch*) ; 

void
frame_base_append_sniffer (struct gdbarch *gdbarch,
			   frame_base_sniffer_ftype *sniffer)
{
  struct frame_base_table *table = frame_base_table (gdbarch);
  append_predicate (table, sniffer);
}