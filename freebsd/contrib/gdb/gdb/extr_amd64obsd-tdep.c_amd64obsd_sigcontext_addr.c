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
struct frame_info {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  AMD64_RSP_REGNUM ; 
 int /*<<< orphan*/  frame_unwind_register_unsigned (struct frame_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CORE_ADDR
amd64obsd_sigcontext_addr (struct frame_info *next_frame)
{
  /* The %rsp register points at `struct sigcontext' upon entry of a
     signal trampoline.  */
  return frame_unwind_register_unsigned (next_frame, AMD64_RSP_REGNUM);
}