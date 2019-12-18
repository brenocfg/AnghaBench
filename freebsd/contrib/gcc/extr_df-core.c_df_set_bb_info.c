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
struct dataflow {void** block_info; } ;

/* Variables and functions */

__attribute__((used)) static void
df_set_bb_info (struct dataflow *dflow, unsigned int index, 
		void *bb_info)
{
  dflow->block_info[index] = bb_info;
}