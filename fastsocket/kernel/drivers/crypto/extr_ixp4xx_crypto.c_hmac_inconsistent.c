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
struct scatterlist {unsigned int length; } ;

/* Variables and functions */
 struct scatterlist* scatterwalk_sg_next (struct scatterlist*) ; 

__attribute__((used)) static int hmac_inconsistent(struct scatterlist *sg, unsigned start,
		unsigned int nbytes)
{
	int offset = 0;

	if (!nbytes)
		return 0;

	for (;;) {
		if (start < offset + sg->length)
			break;

		offset += sg->length;
		sg = scatterwalk_sg_next(sg);
	}
	return (start + nbytes > offset + sg->length);
}