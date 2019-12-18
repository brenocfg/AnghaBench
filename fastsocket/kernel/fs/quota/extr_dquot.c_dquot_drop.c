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
struct inode {int /*<<< orphan*/  i_sb; struct dquot** i_dquot; } ;
struct dquot {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dqptr_sem; } ;

/* Variables and functions */
 int MAXQUOTAS ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dqput (struct dquot*) ; 
 TYPE_1__* sb_dqopt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int dquot_drop(struct inode *inode)
{
	int cnt;
	struct dquot *put[MAXQUOTAS];

	down_write(&sb_dqopt(inode->i_sb)->dqptr_sem);
	for (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		put[cnt] = inode->i_dquot[cnt];
		inode->i_dquot[cnt] = NULL;
	}
	up_write(&sb_dqopt(inode->i_sb)->dqptr_sem);

	for (cnt = 0; cnt < MAXQUOTAS; cnt++)
		dqput(put[cnt]);
	return 0;
}