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
struct igb_ring_container {int /*<<< orphan*/  count; struct igb_ring* ring; } ;
struct igb_ring {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void igb_add_ring(struct igb_ring *ring,
			 struct igb_ring_container *head)
{
	head->ring = ring;
	head->count++;
}