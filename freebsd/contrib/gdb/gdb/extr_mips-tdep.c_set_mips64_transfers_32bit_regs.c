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
struct cmd_list_element {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  gdbarch_info_init (struct gdbarch_info*) ; 
 int /*<<< orphan*/  gdbarch_update_p (struct gdbarch_info) ; 
 scalar_t__ mips64_transfers_32bit_regs_p ; 

__attribute__((used)) static void
set_mips64_transfers_32bit_regs (char *args, int from_tty,
				 struct cmd_list_element *c)
{
  struct gdbarch_info info;
  gdbarch_info_init (&info);
  /* FIXME: cagney/2003-11-15: Should be setting a field in "info"
     instead of relying on globals.  Doing that would let generic code
     handle the search for this specific architecture.  */
  if (!gdbarch_update_p (info))
    {
      mips64_transfers_32bit_regs_p = 0;
      error ("32-bit compatibility mode not supported");
    }
}