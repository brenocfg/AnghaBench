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
typedef  int u32 ;
struct aac_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  OMR; } ;

/* Variables and functions */
 int KERNEL_PANIC ; 
 int KERNEL_UP_AND_RUNNING ; 
 TYPE_1__ MUnit ; 
 int SELF_TEST_FAILED ; 
 int src_readl (struct aac_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int aac_src_check_health(struct aac_dev *dev)
{
	u32 status = src_readl(dev, MUnit.OMR);

	/*
	 *	Check to see if the board failed any self tests.
	 */
	if (unlikely(status & SELF_TEST_FAILED))
		return -1;

	/*
	 *	Check to see if the board panic'd.
	 */
	if (unlikely(status & KERNEL_PANIC))
		return (status >> 16) & 0xFF;
	/*
	 *	Wait for the adapter to be up and running.
	 */
	if (unlikely(!(status & KERNEL_UP_AND_RUNNING)))
		return -3;
	/*
	 *	Everything is OK
	 */
	return 0;
}