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
typedef  int u64 ;
typedef  int u32 ;
struct nfs4_filelayout_segment {int stripe_unit; scalar_t__ pattern_offset; TYPE_1__* dsaddr; } ;
typedef  int loff_t ;
struct TYPE_2__ {int stripe_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,int) ; 

__attribute__((used)) static loff_t
filelayout_get_dense_offset(struct nfs4_filelayout_segment *flseg,
			    loff_t offset)
{
	u32 stripe_width = flseg->stripe_unit * flseg->dsaddr->stripe_count;
	u64 tmp;

	offset -= flseg->pattern_offset;
	tmp = offset;
	do_div(tmp, stripe_width);

	return tmp * flseg->stripe_unit + do_div(offset, flseg->stripe_unit);
}