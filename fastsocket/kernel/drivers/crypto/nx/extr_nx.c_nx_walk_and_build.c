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
struct scatter_walk {int /*<<< orphan*/  sg; } ;
struct nx_sg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCATTERWALK_FROM_SG ; 
 struct nx_sg* nx_build_sg_list (struct nx_sg*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_advance (struct scatter_walk*,unsigned int) ; 
 unsigned int scatterwalk_clamp (struct scatter_walk*,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_done (struct scatter_walk*,int /*<<< orphan*/ ,unsigned int) ; 
 char* scatterwalk_map (struct scatter_walk*,int /*<<< orphan*/ ) ; 
 struct scatterlist* scatterwalk_sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  scatterwalk_start (struct scatter_walk*,struct scatterlist*) ; 
 int /*<<< orphan*/  scatterwalk_unmap (char*,int /*<<< orphan*/ ) ; 
 struct scatterlist* sg_next (int /*<<< orphan*/ ) ; 

struct nx_sg *nx_walk_and_build(struct nx_sg       *nx_dst,
				unsigned int        sglen,
				struct scatterlist *sg_src,
				unsigned int        start,
				unsigned int        src_len)
{
	struct scatter_walk walk;
	struct nx_sg *nx_sg = nx_dst;
	unsigned int n, offset = 0, len = src_len;
	char *dst;

	/* we need to fast forward through @start bytes first */
	for (;;) {
		scatterwalk_start(&walk, sg_src);

		if (start < offset + sg_src->length)
			break;

		offset += sg_src->length;
		sg_src = scatterwalk_sg_next(sg_src);
	}

	/* start - offset is the number of bytes to advance in the scatterlist
	 * element we're currently looking at */
	scatterwalk_advance(&walk, start - offset);

	while (len && nx_sg) {
		n = scatterwalk_clamp(&walk, len);
		if (!n) {
			scatterwalk_start(&walk, sg_next(walk.sg));
			n = scatterwalk_clamp(&walk, len);
		}
		dst = scatterwalk_map(&walk, SCATTERWALK_FROM_SG);

		nx_sg = nx_build_sg_list(nx_sg, dst, n, sglen);
		len -= n;

		scatterwalk_unmap(dst, SCATTERWALK_FROM_SG);
		scatterwalk_advance(&walk, n);
		scatterwalk_done(&walk, SCATTERWALK_FROM_SG, len);
	}

	/* return the moved destination pointer */
	return nx_sg;
}