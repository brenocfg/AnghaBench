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
struct rtc_device {int dummy; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct rtc_device* data; } ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_1__* PDE (struct inode*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  rtc_proc_show ; 
 int single_open (struct file*,int /*<<< orphan*/ ,struct rtc_device*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtc_proc_open(struct inode *inode, struct file *file)
{
	struct rtc_device *rtc = PDE(inode)->data;

	if (!try_module_get(THIS_MODULE))
		return -ENODEV;

	return single_open(file, rtc_proc_show, rtc);
}