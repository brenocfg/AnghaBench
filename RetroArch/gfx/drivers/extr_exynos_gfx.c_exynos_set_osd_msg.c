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
struct font_params {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void exynos_set_osd_msg(void *data, const char *msg,
      const struct font_params *params)
{
   (void)data;
   (void)msg;
   (void)params;
}