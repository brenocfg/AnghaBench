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
struct scatterlist {int length; } ;

/* Variables and functions */
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static int get_sg_count(struct scatterlist *sg_list, int nbytes)
{
	struct scatterlist *sg = sg_list;
	int sg_nents = 0;

	while (nbytes) {
		sg_nents++;
		if (sg->length > nbytes)
			break;
		nbytes -= sg->length;
		sg = sg_next(sg);
	}

	return sg_nents;
}