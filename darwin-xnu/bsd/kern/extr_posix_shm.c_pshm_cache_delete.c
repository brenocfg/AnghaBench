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
struct TYPE_2__ {scalar_t__ le_prev; struct pshmcache* le_next; } ;
struct pshmcache {TYPE_1__ pshm_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct pshmcache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pshm_hash ; 
 int /*<<< orphan*/  pshmnument ; 

__attribute__((used)) static void
pshm_cache_delete(struct pshmcache *pcp)
{
#if DIAGNOSTIC
	if (pcp->pshm_hash.le_prev == 0)
		panic("namecache purge le_prev");
	if (pcp->pshm_hash.le_next == pcp)
		panic("namecache purge le_next");
#endif /* DIAGNOSTIC */
	LIST_REMOVE(pcp, pshm_hash);
	pcp->pshm_hash.le_prev = 0;	
	pshmnument--;
}