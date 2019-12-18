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
struct gdbarch {int /*<<< orphan*/  deprecated_save_dummy_frame_tos; } ;
typedef  int /*<<< orphan*/  gdbarch_deprecated_save_dummy_frame_tos_ftype ;

/* Variables and functions */

void
set_gdbarch_deprecated_save_dummy_frame_tos (struct gdbarch *gdbarch,
                                             gdbarch_deprecated_save_dummy_frame_tos_ftype deprecated_save_dummy_frame_tos)
{
  gdbarch->deprecated_save_dummy_frame_tos = deprecated_save_dummy_frame_tos;
}