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
struct mISDNdevice {int nrbchan; int /*<<< orphan*/  channelmap; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct mISDNdevice* dev_to_mISDN (struct device*) ; 
 scalar_t__ test_channelmap (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t _show_channelmap(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct mISDNdevice *mdev = dev_to_mISDN(dev);
	char *bp = buf;
	int i;

	for (i = 0; i <= mdev->nrbchan; i++)
		*bp++ = test_channelmap(i, mdev->channelmap) ? '1' : '0';

	return bp - buf;
}