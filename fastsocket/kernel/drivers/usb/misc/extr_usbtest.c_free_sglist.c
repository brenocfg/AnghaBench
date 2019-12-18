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
 int /*<<< orphan*/  kfree (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 struct scatterlist* sg_virt (struct scatterlist*) ; 

__attribute__((used)) static void free_sglist (struct scatterlist *sg, int nents)
{
	unsigned		i;

	if (!sg)
		return;
	for (i = 0; i < nents; i++) {
		if (!sg_page(&sg[i]))
			continue;
		kfree (sg_virt(&sg[i]));
	}
	kfree (sg);
}