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
struct s3c2410_hcd_info {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  S3C2410_GPG (int) ; 
 scalar_t__ gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  s3c2410_usb_report_oc (struct s3c2410_hcd_info*,int) ; 

__attribute__((used)) static irqreturn_t
usb_simtec_ocirq(int irq, void *pw)
{
	struct s3c2410_hcd_info *info = pw;

	if (gpio_get_value(S3C2410_GPG(10)) == 0) {
		pr_debug("usb_simtec: over-current irq (oc detected)\n");
		s3c2410_usb_report_oc(info, 3);
	} else {
		pr_debug("usb_simtec: over-current irq (oc cleared)\n");
		s3c2410_usb_report_oc(info, 0);
	}

	return IRQ_HANDLED;
}