#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct radeon_cs_reloc {int dummy; } ;
struct radeon_cs_parser {int chunk_relocs_idx; int nrelocs; int /*<<< orphan*/  validated; TYPE_3__* relocs; TYPE_3__** relocs_ptr; int /*<<< orphan*/  filp; scalar_t__ dma_reloc_idx; struct radeon_cs_chunk* chunks; TYPE_1__* rdev; } ;
struct radeon_cs_chunk {int length_dw; int /*<<< orphan*/ * kdata; } ;
struct drm_radeon_cs_reloc {scalar_t__ handle; int /*<<< orphan*/  flags; int /*<<< orphan*/  read_domains; int /*<<< orphan*/  write_domain; } ;
struct drm_device {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  tbo; } ;
struct TYPE_7__ {int /*<<< orphan*/ * bo; } ;
struct TYPE_9__ {TYPE_2__ tv; int /*<<< orphan*/  rdomain; int /*<<< orphan*/  wdomain; TYPE_5__* bo; } ;
struct TYPE_8__ {scalar_t__ handle; TYPE_4__ lobj; int /*<<< orphan*/  flags; TYPE_5__* robj; int /*<<< orphan*/ * gobj; } ;
struct TYPE_6__ {struct drm_device* ddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,scalar_t__) ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * drm_gem_object_lookup (struct drm_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_5__* gem_to_radeon_bo (int /*<<< orphan*/ *) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_bo_list_add_object (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int radeon_bo_list_validate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int radeon_cs_parser_relocs(struct radeon_cs_parser *p)
{
	struct drm_device *ddev = p->rdev->ddev;
	struct radeon_cs_chunk *chunk;
	unsigned i, j;
	bool duplicate;

	if (p->chunk_relocs_idx == -1) {
		return 0;
	}
	chunk = &p->chunks[p->chunk_relocs_idx];
	p->dma_reloc_idx = 0;
	/* FIXME: we assume that each relocs use 4 dwords */
	p->nrelocs = chunk->length_dw / 4;
	p->relocs_ptr = kcalloc(p->nrelocs, sizeof(void *), GFP_KERNEL);
	if (p->relocs_ptr == NULL) {
		return -ENOMEM;
	}
	p->relocs = kcalloc(p->nrelocs, sizeof(struct radeon_cs_reloc), GFP_KERNEL);
	if (p->relocs == NULL) {
		return -ENOMEM;
	}
	for (i = 0; i < p->nrelocs; i++) {
		struct drm_radeon_cs_reloc *r;

		duplicate = false;
		r = (struct drm_radeon_cs_reloc *)&chunk->kdata[i*4];
		for (j = 0; j < i; j++) {
			if (r->handle == p->relocs[j].handle) {
				p->relocs_ptr[i] = &p->relocs[j];
				duplicate = true;
				break;
			}
		}
		if (!duplicate) {
			p->relocs[i].gobj = drm_gem_object_lookup(ddev,
								  p->filp,
								  r->handle);
			if (p->relocs[i].gobj == NULL) {
				DRM_ERROR("gem object lookup failed 0x%x\n",
					  r->handle);
				return -ENOENT;
			}
			p->relocs_ptr[i] = &p->relocs[i];
			p->relocs[i].robj = gem_to_radeon_bo(p->relocs[i].gobj);
			p->relocs[i].lobj.bo = p->relocs[i].robj;
			p->relocs[i].lobj.wdomain = r->write_domain;
			p->relocs[i].lobj.rdomain = r->read_domains;
			p->relocs[i].lobj.tv.bo = &p->relocs[i].robj->tbo;
			p->relocs[i].handle = r->handle;
			p->relocs[i].flags = r->flags;
			radeon_bo_list_add_object(&p->relocs[i].lobj,
						  &p->validated);

		} else
			p->relocs[i].handle = 0;
	}
	return radeon_bo_list_validate(&p->validated);
}