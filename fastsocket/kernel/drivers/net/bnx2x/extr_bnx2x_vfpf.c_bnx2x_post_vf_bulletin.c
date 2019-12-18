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
struct pf_vf_bulletin_content {int length; int /*<<< orphan*/  crc; int /*<<< orphan*/  version; } ;
struct bnx2x {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {scalar_t__ mapping; } ;

/* Variables and functions */
 struct pf_vf_bulletin_content* BP_VF_BULLETIN (struct bnx2x*,int) ; 
 TYPE_1__* BP_VF_BULLETIN_DMA (struct bnx2x*) ; 
 int BULLETIN_CONTENT_SIZE ; 
 int /*<<< orphan*/  U64_HI (scalar_t__) ; 
 int /*<<< orphan*/  U64_LO (scalar_t__) ; 
 scalar_t__ VF_ACQUIRED ; 
 scalar_t__ VF_ENABLED ; 
 int /*<<< orphan*/  abs_vfid ; 
 int bnx2x_copy32_vf_dmae (struct bnx2x*,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_crc_vf_bulletin (struct bnx2x*,struct pf_vf_bulletin_content*) ; 
 scalar_t__ bnx2x_vf (struct bnx2x*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bulletin_map ; 
 int /*<<< orphan*/  state ; 

int bnx2x_post_vf_bulletin(struct bnx2x *bp, int vf)
{
	struct pf_vf_bulletin_content *bulletin = BP_VF_BULLETIN(bp, vf);
	dma_addr_t pf_addr = BP_VF_BULLETIN_DMA(bp)->mapping +
		vf * BULLETIN_CONTENT_SIZE;
	dma_addr_t vf_addr = bnx2x_vf(bp, vf, bulletin_map);
	int rc;

	/* can only update vf after init took place */
	if (bnx2x_vf(bp, vf, state) != VF_ENABLED &&
	    bnx2x_vf(bp, vf, state) != VF_ACQUIRED)
		return 0;

	/* increment bulletin board version and compute crc */
	bulletin->version++;
	bulletin->length = BULLETIN_CONTENT_SIZE;
	bulletin->crc = bnx2x_crc_vf_bulletin(bp, bulletin);

	/* propagate bulletin board via dmae to vm memory */
	rc = bnx2x_copy32_vf_dmae(bp, false, pf_addr,
				  bnx2x_vf(bp, vf, abs_vfid), U64_HI(vf_addr),
				  U64_LO(vf_addr), bulletin->length / 4);
	return rc;
}