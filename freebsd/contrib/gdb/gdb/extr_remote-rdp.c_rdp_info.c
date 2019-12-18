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
struct TYPE_2__ {int step_info; int target_info; int can_step; int rdi_level; int /*<<< orphan*/  model_info; int /*<<< orphan*/  break_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDP_INFO ; 
 int /*<<< orphan*/  RDP_INFO_ABOUT_BREAK ; 
 int /*<<< orphan*/  RDP_INFO_ABOUT_STEP ; 
 int RDP_INFO_ABOUT_STEP_1 ; 
 int /*<<< orphan*/  RDP_INFO_ABOUT_TARGET ; 
 TYPE_1__ ds ; 
 int /*<<< orphan*/  send_rdp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,...) ; 

__attribute__((used)) static void
rdp_info (void)
{
  send_rdp ("bw-S-W-Z", RDP_INFO, RDP_INFO_ABOUT_STEP,
	    &ds.step_info);
  send_rdp ("bw-S-W-Z", RDP_INFO, RDP_INFO_ABOUT_BREAK,
	    &ds.break_info);
  send_rdp ("bw-S-WW-Z", RDP_INFO, RDP_INFO_ABOUT_TARGET,
	    &ds.target_info,
	    &ds.model_info);

  ds.can_step = ds.step_info & RDP_INFO_ABOUT_STEP_1;

  ds.rdi_level = (ds.target_info >> 5) & 3;
}