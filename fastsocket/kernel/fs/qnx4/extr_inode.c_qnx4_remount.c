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
struct super_block {int dummy; } ;
struct qnx4_sb_info {int /*<<< orphan*/  Version; } ;

/* Variables and functions */
 int MS_RDONLY ; 
 int /*<<< orphan*/  QNX4_VERSION ; 
 struct qnx4_sb_info* qnx4_sb (struct super_block*) ; 

__attribute__((used)) static int qnx4_remount(struct super_block *sb, int *flags, char *data)
{
	struct qnx4_sb_info *qs;

	qs = qnx4_sb(sb);
	qs->Version = QNX4_VERSION;
	*flags |= MS_RDONLY;
	return 0;
}