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
typedef  scalar_t__ u64 ;
struct thash_data {scalar_t__ rid; scalar_t__ vadr; int /*<<< orphan*/  ps; int /*<<< orphan*/  p; } ;

/* Variables and functions */
 scalar_t__ PSIZE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __is_tr_overlap(struct thash_data *trp, u64 rid, u64 sva, u64 eva)
{
	u64 sa1, ea1;

	if (!trp->p || trp->rid != rid)
		return 0;

	sa1 = trp->vadr;
	ea1 = sa1 + PSIZE(trp->ps) - 1;
	eva -= 1;
	if ((sva > ea1) || (sa1 > eva))
		return 0;
	else
		return 1;

}