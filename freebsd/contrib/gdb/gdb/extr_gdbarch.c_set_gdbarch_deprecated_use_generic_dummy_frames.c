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
struct gdbarch {int deprecated_use_generic_dummy_frames; } ;

/* Variables and functions */

void
set_gdbarch_deprecated_use_generic_dummy_frames (struct gdbarch *gdbarch,
                                                 int deprecated_use_generic_dummy_frames)
{
  gdbarch->deprecated_use_generic_dummy_frames = deprecated_use_generic_dummy_frames;
}