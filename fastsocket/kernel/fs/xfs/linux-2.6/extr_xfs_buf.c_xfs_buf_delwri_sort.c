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
typedef  int /*<<< orphan*/  xfs_buftarg_t ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_sort (int /*<<< orphan*/ *,struct list_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_cmp ; 

void
xfs_buf_delwri_sort(
	xfs_buftarg_t	*target,
	struct list_head *list)
{
	list_sort(NULL, list, xfs_buf_cmp);
}