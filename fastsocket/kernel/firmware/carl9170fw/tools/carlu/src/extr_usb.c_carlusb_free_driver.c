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
struct carlu {int* event_pipe; int /*<<< orphan*/ * dev; int /*<<< orphan*/ * fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct carlu*) ; 
 int /*<<< orphan*/  carlfw_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  carlu_free_driver (struct carlu*) ; 
 int /*<<< orphan*/  carlusb_zap_queues (struct carlu*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  libusb_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libusb_release_interface (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void carlusb_free_driver(struct carlu *ar)
{
	if (!IS_ERR_OR_NULL(ar)) {
		if (ar->event_pipe[0] > -1)
			close(ar->event_pipe[0]);

		if (ar->event_pipe[1] > -1)
			close(ar->event_pipe[1]);

		carlusb_zap_queues(ar);
		carlfw_release(ar->fw);
		ar->fw = NULL;

		if (ar->dev) {
			libusb_release_interface(ar->dev, 0);
			libusb_close(ar->dev);
			ar->dev = NULL;
		}
		carlu_free_driver(ar);
	}
}