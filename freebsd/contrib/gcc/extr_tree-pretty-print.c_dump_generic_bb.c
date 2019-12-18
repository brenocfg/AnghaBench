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
typedef  int /*<<< orphan*/  basic_block ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  buffer ; 
 int /*<<< orphan*/  dump_generic_bb_buff (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  maybe_init_pretty_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_flush (int /*<<< orphan*/ *) ; 

void
dump_generic_bb (FILE *file, basic_block bb, int indent, int flags)
{
  maybe_init_pretty_print (file);
  dump_generic_bb_buff (&buffer, bb, indent, flags);
  pp_flush (&buffer);
}