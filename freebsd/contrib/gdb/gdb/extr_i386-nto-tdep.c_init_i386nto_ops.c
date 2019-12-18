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
struct TYPE_2__ {int /*<<< orphan*/  nto_fetch_link_map_offsets; int /*<<< orphan*/  nto_regset_fill; int /*<<< orphan*/  nto_register_area; int /*<<< orphan*/  nto_supply_regset; int /*<<< orphan*/  nto_supply_altregset; int /*<<< orphan*/  nto_supply_fpregset; int /*<<< orphan*/  nto_supply_gregset; int /*<<< orphan*/  nto_regset_id; } ;

/* Variables and functions */
 TYPE_1__ current_nto_target ; 
 int /*<<< orphan*/  i386nto_register_area ; 
 int /*<<< orphan*/  i386nto_regset_fill ; 
 int /*<<< orphan*/  i386nto_regset_id ; 
 int /*<<< orphan*/  i386nto_supply_fpregset ; 
 int /*<<< orphan*/  i386nto_supply_gregset ; 
 int /*<<< orphan*/  i386nto_supply_regset ; 
 int /*<<< orphan*/  i386nto_svr4_fetch_link_map_offsets ; 
 int /*<<< orphan*/  nto_dummy_supply_regset ; 

__attribute__((used)) static void
init_i386nto_ops (void)
{
  current_nto_target.nto_regset_id = i386nto_regset_id;
  current_nto_target.nto_supply_gregset = i386nto_supply_gregset;
  current_nto_target.nto_supply_fpregset = i386nto_supply_fpregset;
  current_nto_target.nto_supply_altregset = nto_dummy_supply_regset;
  current_nto_target.nto_supply_regset = i386nto_supply_regset;
  current_nto_target.nto_register_area = i386nto_register_area;
  current_nto_target.nto_regset_fill = i386nto_regset_fill;
  current_nto_target.nto_fetch_link_map_offsets =
    i386nto_svr4_fetch_link_map_offsets;
}