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
typedef  int /*<<< orphan*/  u8 ;
struct fb_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int i810_probe_i2c_connector(struct fb_info *info, u8 **out_edid,
				    int conn)
{
	return 1;
}