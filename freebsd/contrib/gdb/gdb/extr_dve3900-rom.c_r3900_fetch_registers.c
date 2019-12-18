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
struct TYPE_2__ {int badvaddr; int cause; } ;

/* Variables and functions */
 int PS_REGNUM ; 
 int /*<<< orphan*/  cause_fields ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  fetch_bad_vaddr () ; 
 int /*<<< orphan*/  fetch_bitmapped_register (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* mips_regnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  orig_monitor_fetch_registers (int) ; 
 int /*<<< orphan*/  status_fields ; 

__attribute__((used)) static void
r3900_fetch_registers (int regno)
{
  if (regno == mips_regnum (current_gdbarch)->badvaddr)
    fetch_bad_vaddr ();
  else if (regno == PS_REGNUM)
    fetch_bitmapped_register (PS_REGNUM, status_fields);
  else if (regno == mips_regnum (current_gdbarch)->cause)
    fetch_bitmapped_register (mips_regnum (current_gdbarch)->cause,
			      cause_fields);
  else
    orig_monitor_fetch_registers (regno);
}