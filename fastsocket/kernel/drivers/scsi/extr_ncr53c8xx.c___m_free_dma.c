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
typedef  int /*<<< orphan*/  u_long ;
struct m_pool {int /*<<< orphan*/  nump; } ;
typedef  int /*<<< orphan*/  m_bush_t ;

/* Variables and functions */
 int /*<<< orphan*/  ___del_dma_pool (struct m_pool*) ; 
 struct m_pool* ___get_dma_pool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __m_free (struct m_pool*,void*,int,char*) ; 
 int /*<<< orphan*/  ncr53c8xx_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __m_free_dma(m_bush_t bush, void *m, int size, char *name)
{
	u_long flags;
	struct m_pool *mp;

	spin_lock_irqsave(&ncr53c8xx_lock, flags);
	mp = ___get_dma_pool(bush);
	if (mp)
		__m_free(mp, m, size, name);
	if (mp && !mp->nump)
		___del_dma_pool(mp);
	spin_unlock_irqrestore(&ncr53c8xx_lock, flags);
}