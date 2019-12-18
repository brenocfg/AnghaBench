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
struct ocfs2_super {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ocfs2_drop_dl_inodes (struct ocfs2_super*,int) ; 

void ocfs2_drop_all_dl_inodes(struct ocfs2_super *osb)
{
	__ocfs2_drop_dl_inodes(osb, -1);
}