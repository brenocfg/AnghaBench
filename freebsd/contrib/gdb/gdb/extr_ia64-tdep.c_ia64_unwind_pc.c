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
struct gdbarch {int dummy; } ;
struct frame_info {int dummy; } ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  IA64_IP_REGNUM ; 
 int /*<<< orphan*/  IA64_PSR_REGNUM ; 
 int extract_unsigned_integer (char*,int) ; 
 int /*<<< orphan*/  frame_unwind_register (struct frame_info*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static CORE_ADDR 
ia64_unwind_pc (struct gdbarch *gdbarch, struct frame_info *next_frame)
{
  char buf[8];
  CORE_ADDR ip, psr, pc;

  frame_unwind_register (next_frame, IA64_IP_REGNUM, buf);
  ip = extract_unsigned_integer (buf, 8);
  frame_unwind_register (next_frame, IA64_PSR_REGNUM, buf);
  psr = extract_unsigned_integer (buf, 8);
 
  pc = (ip & ~0xf) | ((psr >> 41) & 3);
  return pc;
}