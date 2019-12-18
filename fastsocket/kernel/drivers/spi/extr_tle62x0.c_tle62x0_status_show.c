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
struct tle62x0_state {unsigned char* rx_buff; int nr_gpio; int /*<<< orphan*/  lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 char* decode_fault (unsigned long) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,...) ; 
 struct tle62x0_state* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int tle62x0_read (struct tle62x0_state*) ; 

__attribute__((used)) static ssize_t tle62x0_status_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct tle62x0_state *st = dev_get_drvdata(dev);
	char *bp = buf;
	unsigned char *buff = st->rx_buff;
	unsigned long fault = 0;
	int ptr;
	int ret;

	mutex_lock(&st->lock);
	ret = tle62x0_read(st);
	dev_dbg(dev, "tle62x0_read() returned %d\n", ret);
	if (ret < 0) {
		mutex_unlock(&st->lock);
		return ret;
	}

	for (ptr = 0; ptr < (st->nr_gpio * 2)/8; ptr += 1) {
		fault <<= 8;
		fault  |= ((unsigned long)buff[ptr]);

		dev_dbg(dev, "byte %d is %02x\n", ptr, buff[ptr]);
	}

	for (ptr = 0; ptr < st->nr_gpio; ptr++) {
		bp += sprintf(bp, "%s ", decode_fault(fault >> (ptr * 2)));
	}

	*bp++ = '\n';

	mutex_unlock(&st->lock);
	return bp - buf;
}