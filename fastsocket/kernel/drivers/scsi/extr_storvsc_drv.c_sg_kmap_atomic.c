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
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_IRQ0 ; 
 void* kmap_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 

__attribute__((used)) static inline unsigned long sg_kmap_atomic(struct scatterlist *sgl, int idx)
{
	void *addr = kmap_atomic(sg_page(sgl + idx), KM_IRQ0);
	return (unsigned long)addr;
}