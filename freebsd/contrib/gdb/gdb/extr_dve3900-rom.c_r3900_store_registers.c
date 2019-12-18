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
struct TYPE_2__ {int cause; } ;

/* Variables and functions */
 int PS_REGNUM ; 
 int /*<<< orphan*/  cause_fields ; 
 int /*<<< orphan*/  current_gdbarch ; 
 TYPE_1__* mips_regnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  orig_monitor_store_registers (int) ; 
 int /*<<< orphan*/  status_fields ; 
 int /*<<< orphan*/  store_bitmapped_register (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
r3900_store_registers (int regno)
{
  if (regno == PS_REGNUM)
    store_bitmapped_register (PS_REGNUM, status_fields);
  else if (regno == mips_regnum (current_gdbarch)->cause)
    store_bitmapped_register (mips_regnum (current_gdbarch)->cause,
			      cause_fields);
  else
    orig_monitor_store_registers (regno);
}