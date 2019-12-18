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
struct target_type {int /*<<< orphan*/  module; } ;

/* Variables and functions */
 struct target_type* __find_target_type (char const*) ; 
 int /*<<< orphan*/  _lock ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct target_type *get_target_type(const char *name)
{
	struct target_type *tt;

	down_read(&_lock);

	tt = __find_target_type(name);
	if (tt && !try_module_get(tt->module))
		tt = NULL;

	up_read(&_lock);
	return tt;
}