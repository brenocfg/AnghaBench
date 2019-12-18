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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct bfad_s {TYPE_1__* pcidev; } ;
struct bfad_buf_info {int size; scalar_t__ phys; int /*<<< orphan*/  virt; } ;
struct bfa_sge_s {int sg_len; void* sg_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bfad_buf_info*) ; 
 struct bfad_buf_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

struct bfad_buf_info *
bfad_fcxp_map_sg(struct bfad_s *bfad, void *payload_kbuf,
		 uint32_t payload_len, uint32_t *num_sgles)
{
	struct bfad_buf_info	*buf_base, *buf_info;
	struct bfa_sge_s	*sg_table;
	int sge_num = 1;

	buf_base = kzalloc((sizeof(struct bfad_buf_info) +
			   sizeof(struct bfa_sge_s)) * sge_num, GFP_KERNEL);
	if (!buf_base)
		return NULL;

	sg_table = (struct bfa_sge_s *) (((uint8_t *)buf_base) +
			(sizeof(struct bfad_buf_info) * sge_num));

	/* Allocate dma coherent memory */
	buf_info = buf_base;
	buf_info->size = payload_len;
	buf_info->virt = dma_alloc_coherent(&bfad->pcidev->dev, buf_info->size,
					&buf_info->phys, GFP_KERNEL);
	if (!buf_info->virt)
		goto out_free_mem;

	/* copy the linear bsg buffer to buf_info */
	memset(buf_info->virt, 0, buf_info->size);
	memcpy(buf_info->virt, payload_kbuf, buf_info->size);

	/*
	 * Setup SG table
	 */
	sg_table->sg_len = buf_info->size;
	sg_table->sg_addr = (void *)(size_t) buf_info->phys;

	*num_sgles = sge_num;

	return buf_base;

out_free_mem:
	kfree(buf_base);
	return NULL;
}