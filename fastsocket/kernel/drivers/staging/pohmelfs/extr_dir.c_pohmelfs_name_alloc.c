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
struct pohmelfs_name {char* data; int /*<<< orphan*/  sync_create_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct pohmelfs_name* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pohmelfs_name *pohmelfs_name_alloc(unsigned int len)
{
	struct pohmelfs_name *n;

	n = kzalloc(sizeof(struct pohmelfs_name) + len, GFP_KERNEL);
	if (!n)
		return NULL;

	INIT_LIST_HEAD(&n->sync_create_entry);

	n->data = (char *)(n+1);

	return n;
}