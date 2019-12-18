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
struct whc_qset {int /*<<< orphan*/  stds; int /*<<< orphan*/  list_node; struct whc* whc; int /*<<< orphan*/  qset_dma; } ;
struct whc {int /*<<< orphan*/  qset_pool; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct whc_qset* dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct whc_qset*,int /*<<< orphan*/ ,int) ; 

struct whc_qset *qset_alloc(struct whc *whc, gfp_t mem_flags)
{
	struct whc_qset *qset;
	dma_addr_t dma;

	qset = dma_pool_alloc(whc->qset_pool, mem_flags, &dma);
	if (qset == NULL)
		return NULL;
	memset(qset, 0, sizeof(struct whc_qset));

	qset->qset_dma = dma;
	qset->whc = whc;

	INIT_LIST_HEAD(&qset->list_node);
	INIT_LIST_HEAD(&qset->stds);

	return qset;
}