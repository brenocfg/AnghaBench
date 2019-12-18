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
struct frame_base_table {struct frame_base const* default_base; } ;
struct frame_base {int dummy; } ;

/* Variables and functions */
 struct frame_base_table* frame_base_table (struct gdbarch*) ; 

void
frame_base_set_default (struct gdbarch *gdbarch,
			const struct frame_base *default_base)
{
  struct frame_base_table *table = frame_base_table (gdbarch);
  table->default_base = default_base;
}