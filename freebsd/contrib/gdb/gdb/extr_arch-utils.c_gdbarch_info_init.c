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
struct gdbarch_info {int /*<<< orphan*/  osabi; int /*<<< orphan*/  byte_order; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ENDIAN_UNKNOWN ; 
 int /*<<< orphan*/  GDB_OSABI_UNINITIALIZED ; 
 int /*<<< orphan*/  memset (struct gdbarch_info*,int /*<<< orphan*/ ,int) ; 

void
gdbarch_info_init (struct gdbarch_info *info)
{
  memset (info, 0, sizeof (struct gdbarch_info));
  info->byte_order = BFD_ENDIAN_UNKNOWN;
  info->osabi = GDB_OSABI_UNINITIALIZED;
}