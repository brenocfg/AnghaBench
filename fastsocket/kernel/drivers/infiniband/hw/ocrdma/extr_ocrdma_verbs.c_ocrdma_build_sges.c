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
struct ocrdma_sge {scalar_t__ len; int /*<<< orphan*/  addr_hi; int /*<<< orphan*/  addr_lo; int /*<<< orphan*/  lrkey; } ;
struct ocrdma_hdr_wqe {int /*<<< orphan*/  total_len; } ;
struct ib_sge {scalar_t__ length; int /*<<< orphan*/  addr; int /*<<< orphan*/  lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct ocrdma_sge*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocrdma_build_sges(struct ocrdma_hdr_wqe *hdr,
			      struct ocrdma_sge *sge, int num_sge,
			      struct ib_sge *sg_list)
{
	int i;

	for (i = 0; i < num_sge; i++) {
		sge[i].lrkey = sg_list[i].lkey;
		sge[i].addr_lo = sg_list[i].addr;
		sge[i].addr_hi = upper_32_bits(sg_list[i].addr);
		sge[i].len = sg_list[i].length;
		hdr->total_len += sg_list[i].length;
	}
	if (num_sge == 0)
		memset(sge, 0, sizeof(*sge));
}