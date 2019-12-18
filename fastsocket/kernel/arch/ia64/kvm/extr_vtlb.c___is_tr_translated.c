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
struct thash_data {scalar_t__ rid; scalar_t__ vadr; int /*<<< orphan*/  ps; scalar_t__ p; } ;

/* Variables and functions */
 scalar_t__ PSIZE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __is_tr_translated(struct thash_data *trp, u64 rid, u64 va)
{
	return ((trp->p) && (trp->rid == rid)
				&& ((va-trp->vadr) < PSIZE(trp->ps)));
}