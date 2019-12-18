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
struct scatterlist {int dummy; } ;
struct rds_iw_scatterlist {unsigned int len; scalar_t__ bytes; scalar_t__ dma_npages; scalar_t__ dma_len; struct scatterlist* list; } ;

/* Variables and functions */

__attribute__((used)) static void rds_iw_set_scatterlist(struct rds_iw_scatterlist *sg,
		struct scatterlist *list, unsigned int sg_len)
{
	sg->list = list;
	sg->len = sg_len;
	sg->dma_len = 0;
	sg->dma_npages = 0;
	sg->bytes = 0;
}