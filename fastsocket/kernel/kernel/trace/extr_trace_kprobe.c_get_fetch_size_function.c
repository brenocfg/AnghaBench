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
struct fetch_type {int /*<<< orphan*/ ** fetch; } ;
typedef  int /*<<< orphan*/ * fetch_func_t ;

/* Variables and functions */
 int FETCH_MTD_END ; 
 size_t FETCH_TYPE_STRING ; 
 size_t FETCH_TYPE_STRSIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct fetch_type const* fetch_type_table ; 

__attribute__((used)) static fetch_func_t get_fetch_size_function(const struct fetch_type *type,
					    fetch_func_t orig_fn)
{
	int i;

	if (type != &fetch_type_table[FETCH_TYPE_STRING])
		return NULL;	/* Only string type needs size function */
	for (i = 0; i < FETCH_MTD_END; i++)
		if (type->fetch[i] == orig_fn)
			return fetch_type_table[FETCH_TYPE_STRSIZE].fetch[i];

	WARN_ON(1);	/* This should not happen */
	return NULL;
}