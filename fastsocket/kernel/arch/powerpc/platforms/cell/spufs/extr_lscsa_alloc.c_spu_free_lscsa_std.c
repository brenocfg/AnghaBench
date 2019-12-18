#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spu_state {TYPE_1__* lscsa; } ;
struct TYPE_2__ {unsigned char* ls; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageReserved (int /*<<< orphan*/ ) ; 
 int LS_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  vfree (TYPE_1__*) ; 
 int /*<<< orphan*/  vmalloc_to_page (unsigned char*) ; 

__attribute__((used)) static void spu_free_lscsa_std(struct spu_state *csa)
{
	/* Clear reserved bit before vfree. */
	unsigned char *p;

	if (csa->lscsa == NULL)
		return;

	for (p = csa->lscsa->ls; p < csa->lscsa->ls + LS_SIZE; p += PAGE_SIZE)
		ClearPageReserved(vmalloc_to_page(p));

	vfree(csa->lscsa);
}