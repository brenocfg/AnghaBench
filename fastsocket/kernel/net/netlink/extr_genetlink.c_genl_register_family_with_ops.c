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
struct genl_ops {int dummy; } ;
struct genl_family {int dummy; } ;

/* Variables and functions */
 int genl_register_family (struct genl_family*) ; 
 int genl_register_ops (struct genl_family*,struct genl_ops*) ; 
 int /*<<< orphan*/  genl_unregister_family (struct genl_family*) ; 

int genl_register_family_with_ops(struct genl_family *family,
	struct genl_ops *ops, size_t n_ops)
{
	int err, i;

	err = genl_register_family(family);
	if (err)
		return err;

	for (i = 0; i < n_ops; ++i, ++ops) {
		err = genl_register_ops(family, ops);
		if (err)
			goto err_out;
	}
	return 0;
err_out:
	genl_unregister_family(family);
	return err;
}