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
struct abituguru3_data {scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ ABIT_UGURU3_CMD ; 
 scalar_t__ ABIT_UGURU3_DATA ; 
 int /*<<< orphan*/  ABIT_UGURU3_DEBUG (char*,int) ; 
 int ABIT_UGURU3_SUCCESS ; 
 int ABIT_UGURU3_SYNCHRONIZE_TIMEOUT ; 
 int EIO ; 
 int abituguru3_wait_for_read (struct abituguru3_data*) ; 
 int abituguru3_wait_while_busy (struct abituguru3_data*) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int abituguru3_synchronize(struct abituguru3_data *data)
{
	int x, timeout = ABIT_UGURU3_SYNCHRONIZE_TIMEOUT;

	if ((x = abituguru3_wait_while_busy(data)) != ABIT_UGURU3_SUCCESS) {
		ABIT_UGURU3_DEBUG("synchronize timeout during initial busy "
			"wait, status: 0x%02x\n", x);
		return -EIO;
	}

	outb(0x20, data->addr + ABIT_UGURU3_DATA);
	if ((x = abituguru3_wait_while_busy(data)) != ABIT_UGURU3_SUCCESS) {
		ABIT_UGURU3_DEBUG("synchronize timeout after sending 0x20, "
			"status: 0x%02x\n", x);
		return -EIO;
	}

	outb(0x10, data->addr + ABIT_UGURU3_CMD);
	if ((x = abituguru3_wait_while_busy(data)) != ABIT_UGURU3_SUCCESS) {
		ABIT_UGURU3_DEBUG("synchronize timeout after sending 0x10, "
			"status: 0x%02x\n", x);
		return -EIO;
	}

	outb(0x00, data->addr + ABIT_UGURU3_CMD);
	if ((x = abituguru3_wait_while_busy(data)) != ABIT_UGURU3_SUCCESS) {
		ABIT_UGURU3_DEBUG("synchronize timeout after sending 0x00, "
			"status: 0x%02x\n", x);
		return -EIO;
	}

	if ((x = abituguru3_wait_for_read(data)) != ABIT_UGURU3_SUCCESS) {
		ABIT_UGURU3_DEBUG("synchronize timeout waiting for read, "
			"status: 0x%02x\n", x);
		return -EIO;
	}

	while ((x = inb(data->addr + ABIT_UGURU3_CMD)) != 0xAC) {
		timeout--;
		if (timeout == 0) {
			ABIT_UGURU3_DEBUG("synchronize timeout cmd does not "
				"hold 0xAC after synchronize, cmd: 0x%02x\n",
				x);
			return -EIO;
		}
		msleep(1);
	}
	return 0;
}