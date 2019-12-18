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
struct net_device {struct airo_info* ml_priv; } ;
struct airo_info {int /*<<< orphan*/  sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SOFTRESET ; 
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  OUT4500 (struct airo_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitbusy (struct airo_info*) ; 

__attribute__((used)) static int reset_card( struct net_device *dev , int lock) {
	struct airo_info *ai = dev->ml_priv;

	if (lock && down_interruptible(&ai->sem))
		return -1;
	waitbusy (ai);
	OUT4500(ai,COMMAND,CMD_SOFTRESET);
	msleep(200);
	waitbusy (ai);
	msleep(200);
	if (lock)
		up(&ai->sem);
	return 0;
}