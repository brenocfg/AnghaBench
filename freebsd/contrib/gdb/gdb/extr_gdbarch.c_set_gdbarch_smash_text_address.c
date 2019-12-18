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
struct gdbarch {int /*<<< orphan*/  smash_text_address; } ;
typedef  int /*<<< orphan*/  gdbarch_smash_text_address_ftype ;

/* Variables and functions */

void
set_gdbarch_smash_text_address (struct gdbarch *gdbarch,
                                gdbarch_smash_text_address_ftype smash_text_address)
{
  gdbarch->smash_text_address = smash_text_address;
}