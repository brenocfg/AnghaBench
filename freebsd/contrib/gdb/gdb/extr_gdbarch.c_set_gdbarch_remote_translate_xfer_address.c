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
struct gdbarch {int /*<<< orphan*/  remote_translate_xfer_address; } ;
typedef  int /*<<< orphan*/  gdbarch_remote_translate_xfer_address_ftype ;

/* Variables and functions */

void
set_gdbarch_remote_translate_xfer_address (struct gdbarch *gdbarch,
                                           gdbarch_remote_translate_xfer_address_ftype remote_translate_xfer_address)
{
  gdbarch->remote_translate_xfer_address = remote_translate_xfer_address;
}