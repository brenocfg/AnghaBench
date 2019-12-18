#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* m_pool_p ;
typedef  int /*<<< orphan*/  m_pool_ident_t ;
struct TYPE_6__ {int /*<<< orphan*/  nump; } ;

/* Variables and functions */
 TYPE_1__* ___cre_dma_pool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ___del_dma_pool (TYPE_1__*) ; 
 TYPE_1__* ___get_dma_pool (int /*<<< orphan*/ ) ; 
 void* __sym_calloc (TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sym53c8xx_lock ; 

void *__sym_calloc_dma(m_pool_ident_t dev_dmat, int size, char *name)
{
	unsigned long flags;
	m_pool_p mp;
	void *m = NULL;

	spin_lock_irqsave(&sym53c8xx_lock, flags);
	mp = ___get_dma_pool(dev_dmat);
	if (!mp)
		mp = ___cre_dma_pool(dev_dmat);
	if (!mp)
		goto out;
	m = __sym_calloc(mp, size, name);
#ifdef	SYM_MEM_FREE_UNUSED
	if (!mp->nump)
		___del_dma_pool(mp);
#endif

 out:
	spin_unlock_irqrestore(&sym53c8xx_lock, flags);
	return m;
}