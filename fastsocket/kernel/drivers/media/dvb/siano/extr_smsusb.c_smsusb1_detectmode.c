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
struct smsusb_device_t {TYPE_1__* udev; } ;
struct TYPE_2__ {char* product; } ;

/* Variables and functions */
 int DEVICE_MODE_NONE ; 
 int /*<<< orphan*/  sms_err (char*) ; 
 int /*<<< orphan*/  sms_info (char*,int,char*) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static void smsusb1_detectmode(void *context, int *mode)
{
	char *product_string =
		((struct smsusb_device_t *) context)->udev->product;

	*mode = DEVICE_MODE_NONE;

	if (!product_string) {
		product_string = "none";
		sms_err("product string not found");
	} else if (strstr(product_string, "DVBH"))
		*mode = 1;
	else if (strstr(product_string, "BDA"))
		*mode = 4;
	else if (strstr(product_string, "DVBT"))
		*mode = 0;
	else if (strstr(product_string, "TDMB"))
		*mode = 2;

	sms_info("%d \"%s\"", *mode, product_string);
}