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
struct file {struct adx_wdt* private_data; } ;
struct adx_wdt {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  adx_wdt_dev ; 
 int /*<<< orphan*/  adx_wdt_set_timeout (struct adx_wdt*,int) ; 
 int /*<<< orphan*/  adx_wdt_start (struct adx_wdt*) ; 
 int /*<<< orphan*/  driver_open ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 struct adx_wdt* platform_get_drvdata (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adx_wdt_open(struct inode *inode, struct file *file)
{
	struct adx_wdt *wdt = platform_get_drvdata(adx_wdt_dev);

	if (test_and_set_bit(0, &driver_open))
		return -EBUSY;

	file->private_data = wdt;
	adx_wdt_set_timeout(wdt, 30);
	adx_wdt_start(wdt);

	return nonseekable_open(inode, file);
}