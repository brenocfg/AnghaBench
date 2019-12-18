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
struct b43legacy_pioqueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_transfers (struct b43legacy_pioqueue*) ; 
 int /*<<< orphan*/  kfree (struct b43legacy_pioqueue*) ; 

__attribute__((used)) static void b43legacy_destroy_pioqueue(struct b43legacy_pioqueue *queue)
{
	if (!queue)
		return;

	cancel_transfers(queue);
	kfree(queue);
}