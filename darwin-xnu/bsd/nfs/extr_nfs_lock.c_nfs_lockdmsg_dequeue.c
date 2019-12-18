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
typedef  int /*<<< orphan*/  LOCKD_MSG_REQUEST ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lmr_next ; 
 int /*<<< orphan*/  nfs_pendlockq ; 

void
nfs_lockdmsg_dequeue(LOCKD_MSG_REQUEST *msgreq)
{
	TAILQ_REMOVE(&nfs_pendlockq, msgreq, lmr_next);
}