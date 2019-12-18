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
struct scatter_walk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  scatterwalk_advance (struct scatter_walk*,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_copychunks (void*,struct scatter_walk*,unsigned int,int) ; 
 int /*<<< orphan*/  scatterwalk_done (struct scatter_walk*,int,int /*<<< orphan*/ ) ; 
 struct scatterlist* scatterwalk_sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  scatterwalk_start (struct scatter_walk*,struct scatterlist*) ; 

void scatterwalk_map_and_copy(void *buf, struct scatterlist *sg,
			      unsigned int start, unsigned int nbytes, int out)
{
	struct scatter_walk walk;
	unsigned int offset = 0;

	if (!nbytes)
		return;

	for (;;) {
		scatterwalk_start(&walk, sg);

		if (start < offset + sg->length)
			break;

		offset += sg->length;
		sg = scatterwalk_sg_next(sg);
	}

	scatterwalk_advance(&walk, start - offset);
	scatterwalk_copychunks(buf, &walk, nbytes, out);
	scatterwalk_done(&walk, out, 0);
}