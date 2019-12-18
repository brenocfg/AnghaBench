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
 int /*<<< orphan*/  get_frame_base (struct frame_info*) ; 

__attribute__((used)) static CORE_ADDR
alphanbsd_sigcontext_addr (struct frame_info *frame)
{
  /* FIXME: This is not correct for all versions of NetBSD/alpha.
     We will probably need to disassemble the trampoline to figure
     out which trampoline frame type we have.  */
  return get_frame_base (frame);
}