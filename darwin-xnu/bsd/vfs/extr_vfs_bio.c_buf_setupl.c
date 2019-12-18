#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ upl_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  TYPE_1__* buf_t ;
struct TYPE_3__ {int b_lflags; int /*<<< orphan*/  b_uploffset; scalar_t__ b_upl; int /*<<< orphan*/  b_flags; } ;

/* Variables and functions */
 int BL_IOBUF ; 
 int /*<<< orphan*/  B_CLUSTER ; 
 int /*<<< orphan*/  EINVAL ; 

errno_t
buf_setupl(buf_t bp, upl_t upl, uint32_t offset)
{

        if ( !(bp->b_lflags & BL_IOBUF) )
	        return (EINVAL);

	if (upl)
	        bp->b_flags |= B_CLUSTER;
	else
	        bp->b_flags &= ~B_CLUSTER;
	bp->b_upl = upl;
	bp->b_uploffset = offset;

	return (0);
}