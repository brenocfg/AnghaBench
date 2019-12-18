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
typedef  int /*<<< orphan*/  u8 ;
struct zfcp_queue_req {int dummy; } ;
struct zfcp_qdio {int dummy; } ;
struct scatterlist {int /*<<< orphan*/  length; } ;
struct qdio_buffer_element {int /*<<< orphan*/  sflags; } ;

/* Variables and functions */
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_virt (struct scatterlist*) ; 
 int zfcp_qdio_fill_sbals (struct zfcp_qdio*,struct zfcp_queue_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_qdio_sbal_limit (struct zfcp_qdio*,struct zfcp_queue_req*,int) ; 
 struct qdio_buffer_element* zfcp_qdio_sbale_req (struct zfcp_qdio*,struct zfcp_queue_req*) ; 

int zfcp_qdio_sbals_from_sg(struct zfcp_qdio *qdio,
			    struct zfcp_queue_req *q_req,
			    u8 sbtype, struct scatterlist *sg,
			    int max_sbals)
{
	struct qdio_buffer_element *sbale;
	int retval;

#if 1 /* FIXME */
	/* figure out last allowed SBAL */
	zfcp_qdio_sbal_limit(qdio, q_req, max_sbals);
#endif

	/* set storage-block type for this request */
	sbale = zfcp_qdio_sbale_req(qdio, q_req);
	sbale->sflags |= sbtype;

	for (; sg; sg = sg_next(sg)) {
		retval = zfcp_qdio_fill_sbals(qdio, q_req, sbtype,
					      sg_virt(sg), sg->length);
		if (retval < 0)
			return retval;
	}

	return 0;
}