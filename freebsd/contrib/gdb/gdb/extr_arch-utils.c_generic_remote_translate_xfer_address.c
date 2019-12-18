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
struct regcache {int dummy; } ;
struct gdbarch {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */

void
generic_remote_translate_xfer_address (struct gdbarch *gdbarch,
				       struct regcache *regcache,
				       CORE_ADDR gdb_addr, int gdb_len,
				       CORE_ADDR * rem_addr, int *rem_len)
{
  *rem_addr = gdb_addr;
  *rem_len = gdb_len;
}