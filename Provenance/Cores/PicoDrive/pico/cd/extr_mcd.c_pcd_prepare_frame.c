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

/* Variables and functions */
 int /*<<< orphan*/  SekCycleAim ; 
 int /*<<< orphan*/  SekCycleAimS68k ; 
 int /*<<< orphan*/  mcd_m68k_cycle_base ; 
 int /*<<< orphan*/  mcd_s68k_cycle_base ; 
 int /*<<< orphan*/  pcd_set_cycle_mult () ; 

void pcd_prepare_frame(void)
{
  pcd_set_cycle_mult();

  // need this because we can't have direct mapping between
  // master<->slave cycle counters because of overflows
  mcd_m68k_cycle_base = SekCycleAim;
  mcd_s68k_cycle_base = SekCycleAimS68k;
}