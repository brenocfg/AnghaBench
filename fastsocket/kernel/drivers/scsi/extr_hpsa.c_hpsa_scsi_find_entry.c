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
struct hpsa_scsi_dev_t {int /*<<< orphan*/  scsi3addr; } ;

/* Variables and functions */
 int DEVICE_CHANGED ; 
 int DEVICE_NOT_FOUND ; 
 int DEVICE_SAME ; 
 int DEVICE_UPDATED ; 
 scalar_t__ SCSI3ADDR_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_the_same (struct hpsa_scsi_dev_t*,struct hpsa_scsi_dev_t*) ; 
 scalar_t__ device_updated (struct hpsa_scsi_dev_t*,struct hpsa_scsi_dev_t*) ; 

__attribute__((used)) static int hpsa_scsi_find_entry(struct hpsa_scsi_dev_t *needle,
	struct hpsa_scsi_dev_t *haystack[], int haystack_size,
	int *index)
{
	int i;
#define DEVICE_NOT_FOUND 0
#define DEVICE_CHANGED 1
#define DEVICE_SAME 2
#define DEVICE_UPDATED 3
	for (i = 0; i < haystack_size; i++) {
		if (haystack[i] == NULL) /* previously removed. */
			continue;
		if (SCSI3ADDR_EQ(needle->scsi3addr, haystack[i]->scsi3addr)) {
			*index = i;
			if (device_is_the_same(needle, haystack[i])) {
				if (device_updated(needle, haystack[i]))
					return DEVICE_UPDATED;
				return DEVICE_SAME;
			} else {
				return DEVICE_CHANGED;
			}
		}
	}
	*index = -1;
	return DEVICE_NOT_FOUND;
}