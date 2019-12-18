#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* m_vtob_p ;
typedef  TYPE_2__* m_pool_p ;
struct TYPE_8__ {int /*<<< orphan*/  nump; TYPE_1__** vtob; } ;
struct TYPE_7__ {struct TYPE_7__* next; } ;

/* Variables and functions */
 int VTOB_HASH_CODE (void*) ; 
 TYPE_1__* __sym_calloc (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  mp0 ; 
 void* sym_m_get_dma_mem_cluster (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static void * ___get_dma_mem_cluster(m_pool_p mp)
{
	m_vtob_p vbp;
	void *vaddr;

	vbp = __sym_calloc(&mp0, sizeof(*vbp), "VTOB");
	if (!vbp)
		goto out_err;

	vaddr = sym_m_get_dma_mem_cluster(mp, vbp);
	if (vaddr) {
		int hc = VTOB_HASH_CODE(vaddr);
		vbp->next = mp->vtob[hc];
		mp->vtob[hc] = vbp;
		++mp->nump;
	}
	return vaddr;
out_err:
	return NULL;
}