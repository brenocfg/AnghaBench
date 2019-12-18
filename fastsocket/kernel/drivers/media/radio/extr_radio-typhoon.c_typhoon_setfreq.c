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
struct typhoon {unsigned long curfreq; } ;

/* Variables and functions */
 int /*<<< orphan*/  typhoon_setfreq_generic (struct typhoon*,unsigned long) ; 

__attribute__((used)) static int typhoon_setfreq(struct typhoon *dev, unsigned long frequency)
{
	typhoon_setfreq_generic(dev, frequency);
	dev->curfreq = frequency;
	return 0;
}