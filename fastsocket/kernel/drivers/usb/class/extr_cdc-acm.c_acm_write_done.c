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
struct acm_wb {scalar_t__ use; } ;
struct acm {int /*<<< orphan*/  control; int /*<<< orphan*/  transmitting; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_autopm_put_interface_async (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acm_write_done(struct acm *acm, struct acm_wb *wb)
{
	wb->use = 0;
	acm->transmitting--;
	usb_autopm_put_interface_async(acm->control);
}