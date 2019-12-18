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
struct TYPE_2__ {int /*<<< orphan*/ * le_prev; struct psemcache* le_next; } ;
struct psemcache {TYPE_1__ psem_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct psemcache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  psem_hash ; 
 int /*<<< orphan*/  psemnument ; 

__attribute__((used)) static void
psem_cache_delete(struct psemcache *pcp)
{
#if DIAGNOSTIC
	if (pcp->psem_hash.le_prev == 0)
		panic("psem namecache purge le_prev");
	if (pcp->psem_hash.le_next == pcp)
		panic("namecache purge le_next");
#endif /* DIAGNOSTIC */
	LIST_REMOVE(pcp, psem_hash);
	pcp->psem_hash.le_prev = NULL;	
	psemnument--;
}