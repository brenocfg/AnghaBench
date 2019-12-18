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
struct v4l2_device {int dummy; } ;
struct gemtek {int io; struct v4l2_device v4l2_dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 scalar_t__ gemtek_verify (struct gemtek*,int) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  release_region (int,int) ; 
 int /*<<< orphan*/  request_region (int,int,char*) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_device*,char*) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_device*,char*,...) ; 
 int /*<<< orphan*/  v4l2_warn (struct v4l2_device*,char*,int) ; 

__attribute__((used)) static int gemtek_probe(struct gemtek *gt)
{
	struct v4l2_device *v4l2_dev = &gt->v4l2_dev;
	int ioports[] = { 0x20c, 0x30c, 0x24c, 0x34c, 0x248, 0x28c };
	int i;

	if (!probe) {
		v4l2_info(v4l2_dev, "Automatic device probing disabled.\n");
		return -1;
	}

	v4l2_info(v4l2_dev, "Automatic device probing enabled.\n");

	for (i = 0; i < ARRAY_SIZE(ioports); ++i) {
		v4l2_info(v4l2_dev, "Trying I/O port 0x%x...\n", ioports[i]);

		if (!request_region(ioports[i], 1, "gemtek-probe")) {
			v4l2_warn(v4l2_dev, "I/O port 0x%x busy!\n",
			       ioports[i]);
			continue;
		}

		if (gemtek_verify(gt, ioports[i])) {
			v4l2_info(v4l2_dev, "Card found from I/O port "
			       "0x%x!\n", ioports[i]);

			release_region(ioports[i], 1);
			gt->io = ioports[i];
			return gt->io;
		}

		release_region(ioports[i], 1);
	}

	v4l2_err(v4l2_dev, "Automatic probing failed!\n");
	return -1;
}