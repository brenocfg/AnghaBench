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
struct vreg {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct vreg*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 struct vreg* vregs ; 

struct vreg *vreg_get(struct device *dev, const char *id)
{
	int n;
	for (n = 0; n < ARRAY_SIZE(vregs); n++) {
		if (!strcmp(vregs[n].name, id))
			return vregs + n;
	}
	return 0;
}