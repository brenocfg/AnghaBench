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
struct frame_unwind {int dummy; } ;
struct frame_info {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  frame_pc_unwind (struct frame_info*) ; 
 scalar_t__ mipsfbsd_in_stub_section (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct frame_unwind const mipsfbsd_stub_frame_unwind ; 

__attribute__((used)) static const struct frame_unwind *
mipsfbsd_stub_frame_sniffer (struct frame_info *next_frame)
{
   CORE_ADDR pc = frame_pc_unwind (next_frame);
   
   if (mipsfbsd_in_stub_section(pc, NULL)) 
     return &mipsfbsd_stub_frame_unwind;
   
   return NULL;
}