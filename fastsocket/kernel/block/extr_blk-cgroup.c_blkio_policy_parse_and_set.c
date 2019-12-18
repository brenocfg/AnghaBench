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
typedef  scalar_t__ u64 ;
struct gendisk {int dummy; } ;
struct TYPE_2__ {unsigned long weight; unsigned int iops; scalar_t__ bps; } ;
struct blkio_policy_node {int plid; int fileid; TYPE_1__ val; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  s ;
typedef  enum blkio_policy_id { ____Placeholder_blkio_policy_id } blkio_policy_id ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
#define  BLKIO_POLICY_PROP 133 
#define  BLKIO_POLICY_THROTL 132 
#define  BLKIO_THROTL_read_bps_device 131 
#define  BLKIO_THROTL_read_iops_device 130 
#define  BLKIO_THROTL_write_bps_device 129 
#define  BLKIO_THROTL_write_iops_device 128 
 unsigned long BLKIO_WEIGHT_MAX ; 
 unsigned long BLKIO_WEIGHT_MIN ; 
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  MKDEV (unsigned long,unsigned long) ; 
 scalar_t__ THROTL_IOPS_MAX ; 
 struct gendisk* get_gendisk (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (char**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 
 int strict_strtoul (char*,int,unsigned long*) ; 
 int /*<<< orphan*/  strict_strtoull (char*,int,scalar_t__*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int blkio_policy_parse_and_set(char *buf,
	struct blkio_policy_node *newpn, enum blkio_policy_id plid, int fileid)
{
	struct gendisk *disk = NULL;
	char *s[4], *p, *major_s = NULL, *minor_s = NULL;
	unsigned long major, minor, temp;
	int i = 0, ret = -EINVAL;
	int part;
	dev_t dev;
	u64 bps, iops;

	memset(s, 0, sizeof(s));

	while ((p = strsep(&buf, " ")) != NULL) {
		if (!*p)
			continue;

		s[i++] = p;

		/* Prevent from inputing too many things */
		if (i == 3)
			break;
	}

	if (i != 2)
		goto out;

	p = strsep(&s[0], ":");
	if (p != NULL)
		major_s = p;
	else
		goto out;

	minor_s = s[0];
	if (!minor_s)
		goto out;

	if (strict_strtoul(major_s, 10, &major))
		goto out;

	if (strict_strtoul(minor_s, 10, &minor))
		goto out;

	dev = MKDEV(major, minor);

	disk = get_gendisk(dev, &part);
	if (!disk || part) {
		ret = -ENODEV;
		goto out;
	}

	newpn->dev = dev;

	if (s[1] == NULL)
		return -EINVAL;

	switch (plid) {
	case BLKIO_POLICY_PROP:
		ret = strict_strtoul(s[1], 10, &temp);
		if (ret || (temp < BLKIO_WEIGHT_MIN && temp > 0) ||
			temp > BLKIO_WEIGHT_MAX)
			goto out;

		newpn->plid = plid;
		newpn->fileid = fileid;
		newpn->val.weight = temp;
		break;
	case BLKIO_POLICY_THROTL:
		switch(fileid) {
		case BLKIO_THROTL_read_bps_device:
		case BLKIO_THROTL_write_bps_device:
			if (strict_strtoull(s[1], 10, &bps))
				goto out;

			newpn->plid = plid;
			newpn->fileid = fileid;
			newpn->val.bps = bps;
			break;
		case BLKIO_THROTL_read_iops_device:
		case BLKIO_THROTL_write_iops_device:
			if (strict_strtoull(s[1], 10, &iops))
				goto out;

			if (iops > THROTL_IOPS_MAX)
				goto out;

			newpn->plid = plid;
			newpn->fileid = fileid;
			newpn->val.iops = (unsigned int)iops;
			break;
		}
		break;
	default:
		BUG();
	}
	ret = 0;
out:
	put_disk(disk);
	return ret;
}