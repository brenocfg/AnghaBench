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
struct zcc_magazine {size_t zcc_magazine_index; int /*<<< orphan*/ ** zcc_elements; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcache_mag_has_elements (struct zcc_magazine*) ; 

void *zcache_mag_pop(struct zcc_magazine *mag)
{
	void	*elem;
	assert(zcache_mag_has_elements(mag));
	elem =  mag->zcc_elements[--mag->zcc_magazine_index];
	/* Ensure pointer to element cannot be accessed after we pop it */
	mag->zcc_elements[mag->zcc_magazine_index] = NULL;
	assert(elem != NULL);
	return elem;
}