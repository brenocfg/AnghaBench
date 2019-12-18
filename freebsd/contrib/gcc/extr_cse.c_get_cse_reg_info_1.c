#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int reg_tick; int reg_in_table; int subreg_ticked; unsigned int reg_qty; int /*<<< orphan*/  timestamp; } ;

/* Variables and functions */
 TYPE_1__* cse_reg_info_table ; 
 int /*<<< orphan*/  cse_reg_info_timestamp ; 

__attribute__((used)) static void
get_cse_reg_info_1 (unsigned int regno)
{
  /* Set TIMESTAMP field to CSE_REG_INFO_TIMESTAMP so that this
     entry will be considered to have been initialized.  */
  cse_reg_info_table[regno].timestamp = cse_reg_info_timestamp;

  /* Initialize the rest of the entry.  */
  cse_reg_info_table[regno].reg_tick = 1;
  cse_reg_info_table[regno].reg_in_table = -1;
  cse_reg_info_table[regno].subreg_ticked = -1;
  cse_reg_info_table[regno].reg_qty = -regno - 1;
}