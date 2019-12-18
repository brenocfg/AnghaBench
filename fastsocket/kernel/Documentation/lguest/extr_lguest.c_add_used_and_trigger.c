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
struct virtqueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_used (struct virtqueue*,unsigned int,int) ; 
 int /*<<< orphan*/  trigger_irq (struct virtqueue*) ; 

__attribute__((used)) static void add_used_and_trigger(struct virtqueue *vq, unsigned head, int len)
{
	add_used(vq, head, len);
	trigger_irq(vq);
}