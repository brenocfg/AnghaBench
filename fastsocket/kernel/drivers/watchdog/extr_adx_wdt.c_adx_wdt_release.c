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
 int /*<<< orphan*/  adx_wdt_stop (struct adx_wdt*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  driver_open ; 

__attribute__((used)) static int adx_wdt_release(struct inode *inode, struct file *file)
{
	struct adx_wdt *wdt = file->private_data;

	adx_wdt_stop(wdt);
	clear_bit(0, &driver_open);

	return 0;
}