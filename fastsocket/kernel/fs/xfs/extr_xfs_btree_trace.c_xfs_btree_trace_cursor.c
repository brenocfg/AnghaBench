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
struct xfs_btree_cur {int* bc_ptrs; scalar_t__* bc_bufs; TYPE_1__* bc_ops; } ;
typedef  int __uint64_t ;
typedef  int /*<<< orphan*/  __uint32_t ;
typedef  int /*<<< orphan*/  __psunsigned_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* trace_enter ) (struct xfs_btree_cur*,char const*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  (* trace_cursor ) (struct xfs_btree_cur*,int /*<<< orphan*/ *,int*,int*) ;} ;

/* Variables and functions */
#define  XBT_ARGS 131 
#define  XBT_ENTRY 130 
#define  XBT_ERROR 129 
#define  XBT_EXIT 128 
 int /*<<< orphan*/  XFS_BTREE_KTRACE_CUR ; 
 int /*<<< orphan*/  stub1 (struct xfs_btree_cur*,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  stub2 (struct xfs_btree_cur*,char const*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void
xfs_btree_trace_cursor(
	const char		*func,
	struct xfs_btree_cur	*cur,
	int			type,
	int			line)
{
	__uint32_t		s0;
	__uint64_t		l0, l1;
	char			*s;

	switch (type) {
	case XBT_ARGS:
		s = "args";
		break;
	case XBT_ENTRY:
		s = "entry";
		break;
	case XBT_ERROR:
		s = "error";
		break;
	case XBT_EXIT:
		s = "exit";
		break;
	default:
		s = "unknown";
		break;
	}

	cur->bc_ops->trace_cursor(cur, &s0, &l0, &l1);
	cur->bc_ops->trace_enter(cur, func, s, XFS_BTREE_KTRACE_CUR, line,
				 s0,
				 l0 >> 32, (int)l0,
				 l1 >> 32, (int)l1,
				 (__psunsigned_t)cur->bc_bufs[0],
				 (__psunsigned_t)cur->bc_bufs[1],
				 (__psunsigned_t)cur->bc_bufs[2],
				 (__psunsigned_t)cur->bc_bufs[3],
				 (cur->bc_ptrs[0] << 16) | cur->bc_ptrs[1],
				 (cur->bc_ptrs[2] << 16) | cur->bc_ptrs[3]);
}