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
struct gmidi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gmidi_transmit (struct gmidi_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gmidi_in_tasklet(unsigned long data)
{
	struct gmidi_device *dev = (struct gmidi_device *)data;

	gmidi_transmit(dev, NULL);
}