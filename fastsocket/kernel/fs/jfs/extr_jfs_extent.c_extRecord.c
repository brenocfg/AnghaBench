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
typedef  int /*<<< orphan*/  xad_t ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  commit_mutex; } ;

/* Variables and functions */
 TYPE_1__* JFS_IP (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txBeginAnon (int /*<<< orphan*/ ) ; 
 int xtUpdate (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ *) ; 

int extRecord(struct inode *ip, xad_t * xp)
{
	int rc;

	txBeginAnon(ip->i_sb);

	mutex_lock(&JFS_IP(ip)->commit_mutex);

	/* update the extent */
	rc = xtUpdate(0, ip, xp);

	mutex_unlock(&JFS_IP(ip)->commit_mutex);
	return rc;
}