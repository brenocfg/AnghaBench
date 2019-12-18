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
typedef  int /*<<< orphan*/  lck_attr_t ;

/* Variables and functions */
 scalar_t__ kalloc (int) ; 
 int /*<<< orphan*/  lck_attr_setdefault (int /*<<< orphan*/ *) ; 

lck_attr_t *
lck_attr_alloc_init(
	void)
{
	lck_attr_t	*attr;

	if ((attr = (lck_attr_t *)kalloc(sizeof(lck_attr_t))) != 0)
		lck_attr_setdefault(attr);

	return(attr);
}