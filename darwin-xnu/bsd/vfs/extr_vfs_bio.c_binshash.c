#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bufhashhdr {TYPE_2__* lh_first; } ;
typedef  TYPE_2__* buf_t ;
struct TYPE_6__ {TYPE_2__* le_next; } ;
struct TYPE_7__ {TYPE_1__ b_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHASHENTCHECK (TYPE_2__*) ; 
 int /*<<< orphan*/  blistenterhead (struct bufhashhdr*,TYPE_2__*) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static __inline__ void 
binshash(buf_t bp, struct bufhashhdr *dp)
{
#if DIAGNOSTIC
	buf_t	nbp;
#endif /* DIAGNOSTIC */

	BHASHENTCHECK(bp);

#if DIAGNOSTIC
	nbp = dp->lh_first;
	for(; nbp != NULL; nbp = nbp->b_hash.le_next) {
		if(nbp == bp) 
			panic("buf already in hashlist");
	}
#endif /* DIAGNOSTIC */

	blistenterhead(dp, bp);
}