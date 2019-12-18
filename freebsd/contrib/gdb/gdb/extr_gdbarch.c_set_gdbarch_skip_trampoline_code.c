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
struct gdbarch {int /*<<< orphan*/  skip_trampoline_code; } ;
typedef  int /*<<< orphan*/  gdbarch_skip_trampoline_code_ftype ;

/* Variables and functions */

void
set_gdbarch_skip_trampoline_code (struct gdbarch *gdbarch,
                                  gdbarch_skip_trampoline_code_ftype skip_trampoline_code)
{
  gdbarch->skip_trampoline_code = skip_trampoline_code;
}