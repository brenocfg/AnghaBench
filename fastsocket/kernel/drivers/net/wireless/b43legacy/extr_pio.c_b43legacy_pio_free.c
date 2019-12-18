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
struct b43legacy_pio {int /*<<< orphan*/ * queue0; int /*<<< orphan*/ * queue1; int /*<<< orphan*/ * queue2; int /*<<< orphan*/ * queue3; } ;
struct b43legacy_wldev {struct b43legacy_pio pio; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43legacy_destroy_pioqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  b43legacy_using_pio (struct b43legacy_wldev*) ; 

void b43legacy_pio_free(struct b43legacy_wldev *dev)
{
	struct b43legacy_pio *pio;

	if (!b43legacy_using_pio(dev))
		return;
	pio = &dev->pio;

	b43legacy_destroy_pioqueue(pio->queue3);
	pio->queue3 = NULL;
	b43legacy_destroy_pioqueue(pio->queue2);
	pio->queue2 = NULL;
	b43legacy_destroy_pioqueue(pio->queue1);
	pio->queue1 = NULL;
	b43legacy_destroy_pioqueue(pio->queue0);
	pio->queue0 = NULL;
}