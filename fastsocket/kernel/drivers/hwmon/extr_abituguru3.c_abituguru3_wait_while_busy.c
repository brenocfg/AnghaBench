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
 scalar_t__ ABIT_UGURU3_DATA ; 
 int ABIT_UGURU3_STATUS_BUSY ; 
 int ABIT_UGURU3_SUCCESS ; 
 int ABIT_UGURU3_WAIT_TIMEOUT ; 
 int inb_p (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int abituguru3_wait_while_busy(struct abituguru3_data *data)
{
	u8 x;
	int timeout = ABIT_UGURU3_WAIT_TIMEOUT;

	while ((x = inb_p(data->addr + ABIT_UGURU3_DATA)) &
			ABIT_UGURU3_STATUS_BUSY) {
		timeout--;
		if (timeout == 0)
			return x;
		/* sleep a bit before our last try, to give the uGuru3 one
		   last chance to respond. */
		if (timeout == 1)
			msleep(1);
	}
	return ABIT_UGURU3_SUCCESS;
}