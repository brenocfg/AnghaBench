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
struct ps_internal {int /*<<< orphan*/  list; } ;
struct path_selector_type {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ps_internal* __find_path_selector_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ps_lock ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ps_internal*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int dm_unregister_path_selector(struct path_selector_type *pst)
{
	struct ps_internal *psi;

	down_write(&_ps_lock);

	psi = __find_path_selector_type(pst->name);
	if (!psi) {
		up_write(&_ps_lock);
		return -EINVAL;
	}

	list_del(&psi->list);

	up_write(&_ps_lock);

	kfree(psi);

	return 0;
}