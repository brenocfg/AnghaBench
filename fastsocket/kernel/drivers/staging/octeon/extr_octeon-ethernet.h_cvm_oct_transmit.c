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
struct net_device {int dummy; } ;

/* Variables and functions */
 int cvm_oct_transmit_qos (struct net_device*,void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cvm_oct_transmit(struct net_device *dev,
				   void *work_queue_entry, int do_free)
{
	return cvm_oct_transmit_qos(dev, work_queue_entry, do_free, 0);
}