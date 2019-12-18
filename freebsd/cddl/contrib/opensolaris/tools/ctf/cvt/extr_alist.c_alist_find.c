#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  al_elements; } ;
typedef  TYPE_1__ alist_t ;
struct TYPE_6__ {void* ale_value; void* ale_name; } ;
typedef  TYPE_2__ alist_el_t ;

/* Variables and functions */
 int /*<<< orphan*/  hash_find (int /*<<< orphan*/ ,TYPE_2__*,void**) ; 

int
alist_find(alist_t *alist, void *name, void **value)
{
	alist_el_t template, *retx;
	void *ret;

	template.ale_name = name;
	if (!hash_find(alist->al_elements, &template, &ret))
		return (0);

	if (value) {
		retx = ret;
		*value = retx->ale_value;
	}

	return (1);
}