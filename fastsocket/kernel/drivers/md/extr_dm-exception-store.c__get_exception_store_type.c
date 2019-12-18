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
struct dm_exception_store_type {int /*<<< orphan*/  module; } ;

/* Variables and functions */
 struct dm_exception_store_type* __find_exception_store_type (char const*) ; 
 int /*<<< orphan*/  _lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dm_exception_store_type *_get_exception_store_type(const char *name)
{
	struct dm_exception_store_type *type;

	spin_lock(&_lock);

	type = __find_exception_store_type(name);

	if (type && !try_module_get(type->module))
		type = NULL;

	spin_unlock(&_lock);

	return type;
}