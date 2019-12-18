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
struct resource {int dummy; } ;
struct platform_device {int id; } ;

/* Variables and functions */
 struct resource const* platform_get_resource_byname (struct platform_device*,unsigned long,char*) ; 
 int snprintf (char*,int,char*,char const*,int) ; 

__attribute__((used)) static inline const struct resource *
excite_nand_get_resource(struct platform_device *d, unsigned long flags,
			 const char *basename)
{
	char buf[80];

	if (snprintf(buf, sizeof buf, "%s_%u", basename, d->id) >= sizeof buf)
		return NULL;
	return platform_get_resource_byname(d, flags, buf);
}