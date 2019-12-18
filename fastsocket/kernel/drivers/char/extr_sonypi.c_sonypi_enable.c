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
struct TYPE_2__ {int model; } ;

/* Variables and functions */
 int /*<<< orphan*/  SONYPI_ACPI_ACTIVE ; 
#define  SONYPI_DEVICE_MODEL_TYPE1 130 
#define  SONYPI_DEVICE_MODEL_TYPE2 129 
#define  SONYPI_DEVICE_MODEL_TYPE3 128 
 scalar_t__ camera ; 
 scalar_t__ compat ; 
 scalar_t__ fnkeyinit ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  sonypi_call1 (int) ; 
 int /*<<< orphan*/  sonypi_call2 (int,int) ; 
 int /*<<< orphan*/  sonypi_camera_on () ; 
 TYPE_1__ sonypi_device ; 
 int /*<<< orphan*/  sonypi_type1_srs () ; 
 int /*<<< orphan*/  sonypi_type2_srs () ; 
 int /*<<< orphan*/  sonypi_type3_srs () ; 

__attribute__((used)) static void sonypi_enable(unsigned int camera_on)
{
	switch (sonypi_device.model) {
	case SONYPI_DEVICE_MODEL_TYPE1:
		sonypi_type1_srs();
		break;
	case SONYPI_DEVICE_MODEL_TYPE2:
		sonypi_type2_srs();
		break;
	case SONYPI_DEVICE_MODEL_TYPE3:
		sonypi_type3_srs();
		break;
	}

	sonypi_call1(0x82);
	sonypi_call2(0x81, 0xff);
	sonypi_call1(compat ? 0x92 : 0x82);

	/* Enable ACPI mode to get Fn key events */
	if (!SONYPI_ACPI_ACTIVE && fnkeyinit)
		outb(0xf0, 0xb2);

	if (camera && camera_on)
		sonypi_camera_on();
}