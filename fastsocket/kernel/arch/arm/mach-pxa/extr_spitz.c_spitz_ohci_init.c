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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPITZ_GPIO_USB_HOST ; 
 int UP2OCR ; 
 int UP2OCR_DMPDE ; 
 int UP2OCR_DPPDE ; 
 int UP2OCR_HXOE ; 
 int UP2OCR_HXS ; 
 int gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int spitz_ohci_init(struct device *dev)
{
	int err;

	err = gpio_request(SPITZ_GPIO_USB_HOST, "USB_HOST");
	if (err)
		return err;

	/* Only Port 2 is connected
	 * Setup USB Port 2 Output Control Register
	 */
	UP2OCR = UP2OCR_HXS | UP2OCR_HXOE | UP2OCR_DPPDE | UP2OCR_DMPDE;

	return gpio_direction_output(SPITZ_GPIO_USB_HOST, 1);
}