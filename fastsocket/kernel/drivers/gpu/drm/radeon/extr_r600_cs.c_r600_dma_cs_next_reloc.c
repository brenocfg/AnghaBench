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
struct radeon_cs_reloc {int dummy; } ;
struct radeon_cs_parser {int chunk_relocs_idx; unsigned int dma_reloc_idx; unsigned int nrelocs; struct radeon_cs_reloc** relocs_ptr; struct radeon_cs_chunk* chunks; } ;
struct radeon_cs_chunk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 

int r600_dma_cs_next_reloc(struct radeon_cs_parser *p,
			   struct radeon_cs_reloc **cs_reloc)
{
	struct radeon_cs_chunk *relocs_chunk;
	unsigned idx;

	*cs_reloc = NULL;
	if (p->chunk_relocs_idx == -1) {
		DRM_ERROR("No relocation chunk !\n");
		return -EINVAL;
	}
	relocs_chunk = &p->chunks[p->chunk_relocs_idx];
	idx = p->dma_reloc_idx;
	if (idx >= p->nrelocs) {
		DRM_ERROR("Relocs at %d after relocations chunk end %d !\n",
			  idx, p->nrelocs);
		return -EINVAL;
	}
	*cs_reloc = p->relocs_ptr[idx];
	p->dma_reloc_idx++;
	return 0;
}