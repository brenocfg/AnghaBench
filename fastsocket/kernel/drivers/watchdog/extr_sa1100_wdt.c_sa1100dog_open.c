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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  OIER ; 
 int /*<<< orphan*/  OIER_E3 ; 
 scalar_t__ OSCR ; 
 scalar_t__ OSMR3 ; 
 int /*<<< orphan*/  OSSR ; 
 int /*<<< orphan*/  OSSR_M3 ; 
 int /*<<< orphan*/  OWER ; 
 int /*<<< orphan*/  OWER_WME ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 scalar_t__ pre_margin ; 
 int /*<<< orphan*/  sa1100wdt_users ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sa1100dog_open(struct inode *inode, struct file *file)
{
	if (test_and_set_bit(1, &sa1100wdt_users))
		return -EBUSY;

	/* Activate SA1100 Watchdog timer */
	OSMR3 = OSCR + pre_margin;
	OSSR = OSSR_M3;
	OWER = OWER_WME;
	OIER |= OIER_E3;
	return nonseekable_open(inode, file);
}