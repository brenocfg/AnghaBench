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
struct mapped_device {int dummy; } ;
struct hd_geometry {unsigned long cylinders; unsigned long heads; unsigned long sectors; unsigned long start; } ;
struct dm_ioctl {int data_start; char* data; scalar_t__ data_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*) ; 
 int EINVAL ; 
 int ENXIO ; 
 unsigned long ULONG_MAX ; 
 int /*<<< orphan*/  dm_put (struct mapped_device*) ; 
 int dm_set_geometry (struct mapped_device*,struct hd_geometry*) ; 
 struct mapped_device* find_device (struct dm_ioctl*) ; 
 scalar_t__ invalid_str (char*,void*) ; 
 int sscanf (char*,char*,unsigned long*,unsigned long*,unsigned long*,unsigned long*,char*) ; 

__attribute__((used)) static int dev_set_geometry(struct dm_ioctl *param, size_t param_size)
{
	int r = -EINVAL, x;
	struct mapped_device *md;
	struct hd_geometry geometry;
	unsigned long indata[4];
	char *geostr = (char *) param + param->data_start;
	char dummy;

	md = find_device(param);
	if (!md)
		return -ENXIO;

	if (geostr < param->data ||
	    invalid_str(geostr, (void *) param + param_size)) {
		DMWARN("Invalid geometry supplied.");
		goto out;
	}

	x = sscanf(geostr, "%lu %lu %lu %lu%c", indata,
		   indata + 1, indata + 2, indata + 3, &dummy);

	if (x != 4) {
		DMWARN("Unable to interpret geometry settings.");
		goto out;
	}

	if (indata[0] > 65535 || indata[1] > 255 ||
	    indata[2] > 255 || indata[3] > ULONG_MAX) {
		DMWARN("Geometry exceeds range limits.");
		goto out;
	}

	geometry.cylinders = indata[0];
	geometry.heads = indata[1];
	geometry.sectors = indata[2];
	geometry.start = indata[3];

	r = dm_set_geometry(md, &geometry);

	param->data_size = 0;

out:
	dm_put(md);
	return r;
}