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
typedef  int u32 ;
struct be_adapter {scalar_t__ db; } ;

/* Variables and functions */
 int PHYSDEV_CONTROL_INP_MASK ; 
 scalar_t__ PHYSDEV_CONTROL_OFFSET ; 
 int SLIPORT_IDLE_TIMEOUT ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  ssleep (int) ; 

__attribute__((used)) static int lancer_wait_idle(struct be_adapter *adapter)
{
#define SLIPORT_IDLE_TIMEOUT 30
	u32 reg_val;
	int status = 0, i;

	for (i = 0; i < SLIPORT_IDLE_TIMEOUT; i++) {
		reg_val = ioread32(adapter->db + PHYSDEV_CONTROL_OFFSET);
		if ((reg_val & PHYSDEV_CONTROL_INP_MASK) == 0)
			break;

		ssleep(1);
	}

	if (i == SLIPORT_IDLE_TIMEOUT)
		status = -1;

	return status;
}