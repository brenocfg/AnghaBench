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
typedef  int u8 ;
struct abituguru3_data {scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ ABIT_UGURU3_CMD ; 
 scalar_t__ ABIT_UGURU3_DATA ; 
 int /*<<< orphan*/  ABIT_UGURU3_DEBUG (char*,int,unsigned int,unsigned int,...) ; 
 int ABIT_UGURU3_SUCCESS ; 
 int EIO ; 
 int abituguru3_synchronize (struct abituguru3_data*) ; 
 int abituguru3_wait_for_read (struct abituguru3_data*) ; 
 int abituguru3_wait_while_busy (struct abituguru3_data*) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int abituguru3_read(struct abituguru3_data *data, u8 bank, u8 offset,
	u8 count, u8 *buf)
{
	int i, x;

	if ((x = abituguru3_synchronize(data)))
		return x;

	outb(0x1A, data->addr + ABIT_UGURU3_DATA);
	if ((x = abituguru3_wait_while_busy(data)) != ABIT_UGURU3_SUCCESS) {
		ABIT_UGURU3_DEBUG("read from 0x%02x:0x%02x timed out after "
			"sending 0x1A, status: 0x%02x\n", (unsigned int)bank,
			(unsigned int)offset, x);
		return -EIO;
	}

	outb(bank, data->addr + ABIT_UGURU3_CMD);
	if ((x = abituguru3_wait_while_busy(data)) != ABIT_UGURU3_SUCCESS) {
		ABIT_UGURU3_DEBUG("read from 0x%02x:0x%02x timed out after "
			"sending the bank, status: 0x%02x\n",
			(unsigned int)bank, (unsigned int)offset, x);
		return -EIO;
	}

	outb(offset, data->addr + ABIT_UGURU3_CMD);
	if ((x = abituguru3_wait_while_busy(data)) != ABIT_UGURU3_SUCCESS) {
		ABIT_UGURU3_DEBUG("read from 0x%02x:0x%02x timed out after "
			"sending the offset, status: 0x%02x\n",
			(unsigned int)bank, (unsigned int)offset, x);
		return -EIO;
	}

	outb(count, data->addr + ABIT_UGURU3_CMD);
	if ((x = abituguru3_wait_while_busy(data)) != ABIT_UGURU3_SUCCESS) {
		ABIT_UGURU3_DEBUG("read from 0x%02x:0x%02x timed out after "
			"sending the count, status: 0x%02x\n",
			(unsigned int)bank, (unsigned int)offset, x);
		return -EIO;
	}

	for (i = 0; i < count; i++) {
		if ((x = abituguru3_wait_for_read(data)) !=
				ABIT_UGURU3_SUCCESS) {
			ABIT_UGURU3_DEBUG("timeout reading byte %d from "
				"0x%02x:0x%02x, status: 0x%02x\n", i,
				(unsigned int)bank, (unsigned int)offset, x);
			break;
		}
		buf[i] = inb(data->addr + ABIT_UGURU3_CMD);
	}
	return i;
}