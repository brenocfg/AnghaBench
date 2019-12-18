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
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_PORT ; 
 int /*<<< orphan*/  de620_flip_ds (struct net_device*) ; 
 int /*<<< orphan*/  de620_ready (struct net_device*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
de620_put_byte(struct net_device *dev, byte value)
{
	/* The de620_ready() makes 7 loops, on the average, on a DX2/66 */
	de620_ready(dev);
	outb(value, DATA_PORT);
	de620_flip_ds(dev);
}