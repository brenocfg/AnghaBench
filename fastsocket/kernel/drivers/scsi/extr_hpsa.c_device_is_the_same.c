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
struct hpsa_scsi_dev_t {scalar_t__ devtype; scalar_t__ bus; int /*<<< orphan*/  vendor; int /*<<< orphan*/  model; int /*<<< orphan*/  device_id; int /*<<< orphan*/  scsi3addr; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int device_is_the_same(struct hpsa_scsi_dev_t *dev1,
	struct hpsa_scsi_dev_t *dev2)
{
	/* we compare everything except lun and target as these
	 * are not yet assigned.  Compare parts likely
	 * to differ first
	 */
	if (memcmp(dev1->scsi3addr, dev2->scsi3addr,
		sizeof(dev1->scsi3addr)) != 0)
		return 0;
	if (memcmp(dev1->device_id, dev2->device_id,
		sizeof(dev1->device_id)) != 0)
		return 0;
	if (memcmp(dev1->model, dev2->model, sizeof(dev1->model)) != 0)
		return 0;
	if (memcmp(dev1->vendor, dev2->vendor, sizeof(dev1->vendor)) != 0)
		return 0;
	if (dev1->devtype != dev2->devtype)
		return 0;
	if (dev1->bus != dev2->bus)
		return 0;
	return 1;
}