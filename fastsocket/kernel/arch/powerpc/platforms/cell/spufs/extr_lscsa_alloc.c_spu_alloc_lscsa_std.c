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
struct spu_state {struct spu_lscsa* lscsa; } ;
struct spu_lscsa {unsigned char* ls; } ;

/* Variables and functions */
 int ENOMEM ; 
 int LS_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageReserved (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct spu_lscsa*,int /*<<< orphan*/ ,int) ; 
 struct spu_lscsa* vmalloc (int) ; 
 int /*<<< orphan*/  vmalloc_to_page (unsigned char*) ; 

__attribute__((used)) static int spu_alloc_lscsa_std(struct spu_state *csa)
{
	struct spu_lscsa *lscsa;
	unsigned char *p;

	lscsa = vmalloc(sizeof(struct spu_lscsa));
	if (!lscsa)
		return -ENOMEM;
	memset(lscsa, 0, sizeof(struct spu_lscsa));
	csa->lscsa = lscsa;

	/* Set LS pages reserved to allow for user-space mapping. */
	for (p = lscsa->ls; p < lscsa->ls + LS_SIZE; p += PAGE_SIZE)
		SetPageReserved(vmalloc_to_page(p));

	return 0;
}