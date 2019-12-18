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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct device_node* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 struct device_node* of_find_node_by_path (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 char const* strrchr (char const*,char) ; 

__attribute__((used)) static struct device_node *derive_parent(const char *path)
{
	struct device_node *parent = NULL;
	char *parent_path = "/";
	size_t parent_path_len = strrchr(path, '/') - path + 1;

	/* reject if path is "/" */
	if (!strcmp(path, "/"))
		return ERR_PTR(-EINVAL);

	if (strrchr(path, '/') != path) {
		parent_path = kmalloc(parent_path_len, GFP_KERNEL);
		if (!parent_path)
			return ERR_PTR(-ENOMEM);
		strlcpy(parent_path, path, parent_path_len);
	}
	parent = of_find_node_by_path(parent_path);
	if (!parent)
		return ERR_PTR(-EINVAL);
	if (strcmp(parent_path, "/"))
		kfree(parent_path);
	return parent;
}