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
 int /*<<< orphan*/  htab_traverse_noresize (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ machopic_indirections ; 
 int /*<<< orphan*/  machopic_output_indirection ; 

void
machopic_finish (FILE *asm_out_file)
{
  if (machopic_indirections)
    htab_traverse_noresize (machopic_indirections,
			    machopic_output_indirection,
			    asm_out_file);
}