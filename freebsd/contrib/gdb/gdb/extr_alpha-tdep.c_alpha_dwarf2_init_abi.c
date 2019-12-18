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
struct gdbarch_info {int dummy; } ;
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwarf2_frame_base_sniffer ; 
 int /*<<< orphan*/  dwarf2_frame_sniffer ; 
 int /*<<< orphan*/  frame_base_append_sniffer (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_unwind_append_sniffer (struct gdbarch*,int /*<<< orphan*/ ) ; 

void
alpha_dwarf2_init_abi (struct gdbarch_info info, struct gdbarch *gdbarch)
{
  frame_unwind_append_sniffer (gdbarch, dwarf2_frame_sniffer);
  frame_base_append_sniffer (gdbarch, dwarf2_frame_base_sniffer);
}