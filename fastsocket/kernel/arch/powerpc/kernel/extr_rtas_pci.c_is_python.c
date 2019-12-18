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
struct device_node {int dummy; } ;

/* Variables and functions */
 char* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strstr (char const*,char*) ; 

__attribute__((used)) static int is_python(struct device_node *dev)
{
	const char *model = of_get_property(dev, "model", NULL);

	if (model && strstr(model, "Python"))
		return 1;

	return 0;
}