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
struct bufhashhdr {int dummy; } ;
typedef  int /*<<< orphan*/  buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHASHENTCHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blistenterhead (struct bufhashhdr*,int /*<<< orphan*/ ) ; 

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