#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* m_vtob_p ;
typedef  TYPE_2__* m_pool_p ;
struct TYPE_6__ {int /*<<< orphan*/  dev_dmat; } ;
struct TYPE_5__ {int /*<<< orphan*/  baddr; int /*<<< orphan*/  vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYM_MEM_CLUSTER_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sym_m_free_dma_mem_cluster(m_pool_p mp, m_vtob_p vbp)
{
	dma_free_coherent(mp->dev_dmat, SYM_MEM_CLUSTER_SIZE, vbp->vaddr,
			vbp->baddr);
}