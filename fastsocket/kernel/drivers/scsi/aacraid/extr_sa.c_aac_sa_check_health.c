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
struct aac_dev {int dummy; } ;

/* Variables and functions */
 long KERNEL_PANIC ; 
 long KERNEL_UP_AND_RUNNING ; 
 int /*<<< orphan*/  Mailbox7 ; 
 long SELF_TEST_FAILED ; 
 long sa_readl (struct aac_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aac_sa_check_health(struct aac_dev *dev)
{
	long status = sa_readl(dev, Mailbox7);

	/*
	 *	Check to see if the board failed any self tests.
	 */
	if (status & SELF_TEST_FAILED)
		return -1;
	/*
	 *	Check to see if the board panic'd while booting.
	 */
	if (status & KERNEL_PANIC)
		return -2;
	/*
	 *	Wait for the adapter to be up and running. Wait up to 3 minutes
	 */
	if (!(status & KERNEL_UP_AND_RUNNING))
		return -3;
	/*
	 *	Everything is OK
	 */
	return 0;
}