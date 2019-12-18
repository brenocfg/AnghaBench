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
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tcr; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int TXx9_TMTCR_TCE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int __raw_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 scalar_t__ nowayout ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txx9wdt_alive ; 
 TYPE_1__* txx9wdt_reg ; 
 int /*<<< orphan*/  txx9wdt_start () ; 

__attribute__((used)) static int txx9wdt_open(struct inode *inode, struct file *file)
{
	if (test_and_set_bit(0, &txx9wdt_alive))
		return -EBUSY;

	if (__raw_readl(&txx9wdt_reg->tcr) & TXx9_TMTCR_TCE) {
		clear_bit(0, &txx9wdt_alive);
		return -EBUSY;
	}

	if (nowayout)
		__module_get(THIS_MODULE);

	txx9wdt_start();
	return nonseekable_open(inode, file);
}