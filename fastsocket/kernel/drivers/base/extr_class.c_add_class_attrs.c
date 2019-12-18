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
struct class {int /*<<< orphan*/ * class_attrs; } ;

/* Variables and functions */
 scalar_t__ attr_name (int /*<<< orphan*/ ) ; 
 int class_create_file (struct class*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_remove_file (struct class*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_class_attrs(struct class *cls)
{
	int i;
	int error = 0;

	if (cls->class_attrs) {
		for (i = 0; attr_name(cls->class_attrs[i]); i++) {
			error = class_create_file(cls, &cls->class_attrs[i]);
			if (error)
				goto error;
		}
	}
done:
	return error;
error:
	while (--i >= 0)
		class_remove_file(cls, &cls->class_attrs[i]);
	goto done;
}