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
struct df_scan_bb_info {int dummy; } ;
struct dataflow {unsigned int block_info_size; scalar_t__* block_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_assert (int) ; 

struct df_scan_bb_info *
df_scan_get_bb_info (struct dataflow *dflow, unsigned int index)
{
  gcc_assert (index < dflow->block_info_size); 
  return (struct df_scan_bb_info *) dflow->block_info[index];
}