#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int intmax_t ;
struct TYPE_5__ {int dn_value; int dn_flags; } ;
typedef  TYPE_1__ dt_node_t ;

/* Variables and functions */
 int DT_NF_SIGNED ; 
 int NBBY ; 
 size_t dt_node_type_size (TYPE_1__*) ; 

__attribute__((used)) static void
dt_cast(dt_node_t *lp, dt_node_t *rp)
{
	size_t srcsize = dt_node_type_size(rp);
	size_t dstsize = dt_node_type_size(lp);

	if (dstsize < srcsize) {
		int n = (sizeof (uint64_t) - dstsize) * NBBY;
		rp->dn_value <<= n;
		rp->dn_value >>= n;
	} else if (dstsize > srcsize) {
		int n = (sizeof (uint64_t) - srcsize) * NBBY;
		int s = (dstsize - srcsize) * NBBY;

		rp->dn_value <<= n;
		if (rp->dn_flags & DT_NF_SIGNED) {
			rp->dn_value = (intmax_t)rp->dn_value >> s;
			rp->dn_value >>= n - s;
		} else {
			rp->dn_value >>= n;
		}
	}
}