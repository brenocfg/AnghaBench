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
struct fscache_object {int /*<<< orphan*/ * cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  fscache_cookie_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_objlist_remove (struct fscache_object*) ; 

void fscache_object_destroy(struct fscache_object *object)
{
	fscache_objlist_remove(object);

	/* We can get rid of the cookie now */
	fscache_cookie_put(object->cookie);
	object->cookie = NULL;
}