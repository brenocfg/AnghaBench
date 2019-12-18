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

/* Variables and functions */
#define  AUXIO_TYPE_EBUS 129 
#define  AUXIO_TYPE_SBUS 128 
 int /*<<< orphan*/  __auxio_sbus_set_lte (int) ; 
 int auxio_devtype ; 

void auxio_set_lte(int on)
{
	switch(auxio_devtype) {
	case AUXIO_TYPE_SBUS:
		__auxio_sbus_set_lte(on);
		break;
	case AUXIO_TYPE_EBUS:
		/* FALL-THROUGH */
	default:
		break;
	}
}