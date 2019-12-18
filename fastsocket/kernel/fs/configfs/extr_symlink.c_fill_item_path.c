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
struct config_item {struct config_item* ci_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_item_name (struct config_item*) ; 
 int /*<<< orphan*/  configfs_is_root (struct config_item*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fill_item_path(struct config_item * item, char * buffer, int length)
{
	struct config_item * p;

	--length;
	for (p = item; p && !configfs_is_root(p); p = p->ci_parent) {
		int cur = strlen(config_item_name(p));

		/* back up enough to print this bus id with '/' */
		length -= cur;
		strncpy(buffer + length,config_item_name(p),cur);
		*(buffer + --length) = '/';
	}
}