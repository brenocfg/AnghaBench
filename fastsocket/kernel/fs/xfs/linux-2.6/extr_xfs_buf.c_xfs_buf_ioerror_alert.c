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
struct xfs_buf {int /*<<< orphan*/  b_error; TYPE_1__* b_target; } ;
typedef  int /*<<< orphan*/  __uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  bt_mount; } ;

/* Variables and functions */
 scalar_t__ XFS_BUF_ADDR (struct xfs_buf*) ; 
 int /*<<< orphan*/  XFS_BUF_COUNT (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_alert (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
xfs_buf_ioerror_alert(
	struct xfs_buf		*bp,
	const char		*func)
{
	xfs_alert(bp->b_target->bt_mount,
"metadata I/O error: block 0x%llx (\"%s\") error %d buf count %zd",
		(__uint64_t)XFS_BUF_ADDR(bp), func,
		bp->b_error, XFS_BUF_COUNT(bp));
}