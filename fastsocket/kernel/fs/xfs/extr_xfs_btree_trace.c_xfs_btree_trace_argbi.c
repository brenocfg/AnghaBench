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
struct xfs_buf {int dummy; } ;
struct xfs_btree_cur {TYPE_1__* bc_ops; } ;
typedef  int /*<<< orphan*/  __psunsigned_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* trace_enter ) (struct xfs_btree_cur*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  XBT_ARGS ; 
 int /*<<< orphan*/  XFS_BTREE_KTRACE_ARGBI ; 
 int /*<<< orphan*/  stub1 (struct xfs_btree_cur*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
xfs_btree_trace_argbi(
	const char		*func,
	struct xfs_btree_cur	*cur,
	struct xfs_buf		*b,
	int			i,
	int			line)
{
	cur->bc_ops->trace_enter(cur, func, XBT_ARGS, XFS_BTREE_KTRACE_ARGBI,
				 line, (__psunsigned_t)b, i, 0, 0, 0, 0, 0,
				 0, 0, 0, 0);
}