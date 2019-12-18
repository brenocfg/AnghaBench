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
struct target_ops {int dummy; } ;
struct TYPE_2__ {int target_info; int /*<<< orphan*/  break_info; int /*<<< orphan*/  step_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  breakinfo ; 
 TYPE_1__ ds ; 
 int /*<<< orphan*/  dump_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,int) ; 
 int /*<<< orphan*/  stepinfo ; 

__attribute__((used)) static void
remote_rdp_files_info (struct target_ops *target)
{
  printf_filtered ("Target capabilities:\n");
  dump_bits (stepinfo, ds.step_info);
  dump_bits (breakinfo, ds.break_info);
  printf_unfiltered ("target level RDI %x\n", (ds.target_info >> 5) & 3);
}