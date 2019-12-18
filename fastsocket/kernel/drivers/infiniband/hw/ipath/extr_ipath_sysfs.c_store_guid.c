#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned short u8 ;
struct ipath_devdata {int ipath_nguid; TYPE_2__* verbs_dev; scalar_t__ ipath_guid; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ __be64 ;
struct TYPE_3__ {scalar_t__ node_guid; } ;
struct TYPE_4__ {TYPE_1__ ibdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct ipath_devdata* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  ipath_dev_err (struct ipath_devdata*,char*) ; 
 int sscanf (char const*,char*,unsigned short*,unsigned short*,unsigned short*,unsigned short*,unsigned short*,unsigned short*,unsigned short*,unsigned short*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static ssize_t store_guid(struct device *dev,
			 struct device_attribute *attr,
			  const char *buf,
			  size_t count)
{
	struct ipath_devdata *dd = dev_get_drvdata(dev);
	ssize_t ret;
	unsigned short guid[8];
	__be64 new_guid;
	u8 *ng;
	int i;

	if (sscanf(buf, "%hx:%hx:%hx:%hx:%hx:%hx:%hx:%hx",
		   &guid[0], &guid[1], &guid[2], &guid[3],
		   &guid[4], &guid[5], &guid[6], &guid[7]) != 8)
		goto invalid;

	ng = (u8 *) &new_guid;

	for (i = 0; i < 8; i++) {
		if (guid[i] > 0xff)
			goto invalid;
		ng[i] = guid[i];
	}

	if (new_guid == 0)
		goto invalid;

	dd->ipath_guid = new_guid;
	dd->ipath_nguid = 1;
	if (dd->verbs_dev)
		dd->verbs_dev->ibdev.node_guid = new_guid;

	ret = strlen(buf);
	goto bail;

invalid:
	ipath_dev_err(dd, "attempt to set invalid GUID\n");
	ret = -EINVAL;

bail:
	return ret;
}