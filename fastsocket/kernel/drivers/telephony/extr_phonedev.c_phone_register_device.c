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
struct phone_device {int minor; } ;

/* Variables and functions */
 int ENFILE ; 
 int PHONE_NUM_DEVICES ; 
 int PHONE_UNIT_ANY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct phone_device** phone_device ; 
 int /*<<< orphan*/  phone_lock ; 

int phone_register_device(struct phone_device *p, int unit)
{
	int base;
	int end;
	int i;

	base = 0;
	end = PHONE_NUM_DEVICES - 1;

	if (unit != PHONE_UNIT_ANY) {
		base = unit;
		end = unit + 1;  /* enter the loop at least one time */
	}
	
	mutex_lock(&phone_lock);
	for (i = base; i < end; i++) {
		if (phone_device[i] == NULL) {
			phone_device[i] = p;
			p->minor = i;
			mutex_unlock(&phone_lock);
			return 0;
		}
	}
	mutex_unlock(&phone_lock);
	return -ENFILE;
}