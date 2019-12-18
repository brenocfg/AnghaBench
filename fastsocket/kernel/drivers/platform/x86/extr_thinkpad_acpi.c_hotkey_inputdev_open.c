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
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EBUSY ; 
#define  TPACPI_LIFE_EXITING 130 
#define  TPACPI_LIFE_INIT 129 
#define  TPACPI_LIFE_RUNNING 128 
 int /*<<< orphan*/  hotkey_poll_setup_safe (int) ; 
 int tpacpi_lifecycle ; 

__attribute__((used)) static int hotkey_inputdev_open(struct input_dev *dev)
{
	switch (tpacpi_lifecycle) {
	case TPACPI_LIFE_INIT:
	case TPACPI_LIFE_RUNNING:
		hotkey_poll_setup_safe(false);
		return 0;
	case TPACPI_LIFE_EXITING:
		return -EBUSY;
	}

	/* Should only happen if tpacpi_lifecycle is corrupt */
	BUG();
	return -EBUSY;
}