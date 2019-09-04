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
typedef  int /*<<< orphan*/  ppnum_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 scalar_t__ phystokv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptoa (int /*<<< orphan*/ ) ; 

void
fillPage(
	ppnum_t pn,
	unsigned int fill)
{
	unsigned int   *addr;
	int             count;

	addr = (unsigned int *) phystokv(ptoa(pn));
	count = PAGE_SIZE / sizeof(unsigned int);
	while (count--)
		*addr++ = fill;
}