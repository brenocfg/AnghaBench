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

/* Variables and functions */
 int M_LAST ; 
 int /*<<< orphan*/  kfree_addr (void*) ; 
 int /*<<< orphan*/  panic (char*) ; 

void
_FREE(
	void		*addr,
	int		type)
{
	if (type >= M_LAST)
		panic("_free TYPE");

	if (!addr)
		return; /* correct (convenient bsd kernel legacy) */

	kfree_addr(addr);
}