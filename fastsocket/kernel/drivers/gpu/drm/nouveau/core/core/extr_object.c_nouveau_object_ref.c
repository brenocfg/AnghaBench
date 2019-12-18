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
struct nouveau_object {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_object_dtor (struct nouveau_object*) ; 
 int /*<<< orphan*/  nv_trace (struct nouveau_object*,char*,int /*<<< orphan*/ ) ; 

void
nouveau_object_ref(struct nouveau_object *obj, struct nouveau_object **ref)
{
	if (obj) {
		atomic_inc(&obj->refcount);
		nv_trace(obj, "inc() == %d\n", atomic_read(&obj->refcount));
	}

	if (*ref) {
		int dead = atomic_dec_and_test(&(*ref)->refcount);
		nv_trace(*ref, "dec() == %d\n", atomic_read(&(*ref)->refcount));
		if (dead)
			nouveau_object_dtor(*ref);
	}

	*ref = obj;
}