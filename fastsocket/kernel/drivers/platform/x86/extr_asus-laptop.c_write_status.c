#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_2__ {int status; } ;

/* Variables and functions */
#define  GLED_ON 130 
#define  GPS_ON 129 
#define  MLED_ON 128 
 int /*<<< orphan*/  gps_off_handle ; 
 int /*<<< orphan*/  gps_on_handle ; 
 TYPE_1__* hotk ; 
 int /*<<< orphan*/  pr_warning (char*,int) ; 
 scalar_t__ write_acpi_int (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void write_status(acpi_handle handle, int out, int mask)
{
	hotk->status = (out) ? (hotk->status | mask) : (hotk->status & ~mask);

	switch (mask) {
	case MLED_ON:
		out = !(out & 0x1);
		break;
	case GLED_ON:
		out = (out & 0x1) + 1;
		break;
	case GPS_ON:
		handle = (out) ? gps_on_handle : gps_off_handle;
		out = 0x02;
		break;
	default:
		out &= 0x1;
		break;
	}

	if (write_acpi_int(handle, NULL, out, NULL))
		pr_warning(" write failed %x\n", mask);
}