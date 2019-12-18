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
struct carlu {int /*<<< orphan*/  rx_interrupt; int /*<<< orphan*/ * rx_ring; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libusb_free_transfer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void carlusb_free_rings(struct carlu *ar)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(ar->rx_ring); i++)
		libusb_free_transfer(ar->rx_ring[i]);

	libusb_free_transfer(ar->rx_interrupt);
}