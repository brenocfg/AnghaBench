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
 struct device_node* of_find_node_by_name (int /*<<< orphan*/ *,char*) ; 
 char* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int /*<<< orphan*/ ) ; 

int pmac_has_backlight_type(const char *type)
{
	struct device_node* bk_node = of_find_node_by_name(NULL, "backlight");

	if (bk_node) {
		const char *prop = of_get_property(bk_node,
				"backlight-control", NULL);
		if (prop && strncmp(prop, type, strlen(type)) == 0) {
			of_node_put(bk_node);
			return 1;
		}
		of_node_put(bk_node);
	}

	return 0;
}