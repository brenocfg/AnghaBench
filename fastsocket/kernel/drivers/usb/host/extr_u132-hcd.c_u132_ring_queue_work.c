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
struct u132_ring {int dummy; } ;
struct u132 {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u132_ring_requeue_work (struct u132*,struct u132_ring*,unsigned int) ; 

__attribute__((used)) static void u132_ring_queue_work(struct u132 *u132, struct u132_ring *ring,
	unsigned int delta)
{
	kref_get(&u132->kref);
	u132_ring_requeue_work(u132, ring, delta);
	return;
}