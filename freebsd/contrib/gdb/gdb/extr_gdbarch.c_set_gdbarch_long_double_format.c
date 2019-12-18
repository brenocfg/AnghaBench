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
struct gdbarch {struct floatformat const* long_double_format; } ;
struct floatformat {int dummy; } ;

/* Variables and functions */

void
set_gdbarch_long_double_format (struct gdbarch *gdbarch,
                                const struct floatformat * long_double_format)
{
  gdbarch->long_double_format = long_double_format;
}