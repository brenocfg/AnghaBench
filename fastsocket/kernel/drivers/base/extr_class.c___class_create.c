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
struct module {int dummy; } ;
struct lock_class_key {int dummy; } ;
struct class {char const* name; int /*<<< orphan*/  class_release; struct module* owner; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct class* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __class_register (struct class*,struct lock_class_key*) ; 
 int /*<<< orphan*/  class_create_release ; 
 int /*<<< orphan*/  kfree (struct class*) ; 
 struct class* kzalloc (int,int /*<<< orphan*/ ) ; 

struct class *__class_create(struct module *owner, const char *name,
			     struct lock_class_key *key)
{
	struct class *cls;
	int retval;

	cls = kzalloc(sizeof(*cls), GFP_KERNEL);
	if (!cls) {
		retval = -ENOMEM;
		goto error;
	}

	cls->name = name;
	cls->owner = owner;
	cls->class_release = class_create_release;

	retval = __class_register(cls, key);
	if (retval)
		goto error;

	return cls;

error:
	kfree(cls);
	return ERR_PTR(retval);
}