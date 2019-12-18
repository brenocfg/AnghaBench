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
struct zram {int /*<<< orphan*/  disk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct zram* devices ; 
 struct device* disk_to_dev (int /*<<< orphan*/ ) ; 
 int num_devices ; 

__attribute__((used)) static struct zram *dev_to_zram(struct device *dev)
{
	int i;
	struct zram *zram = NULL;

	for (i = 0; i < num_devices; i++) {
		zram = &devices[i];
		if (disk_to_dev(zram->disk) == dev)
			break;
	}

	return zram;
}