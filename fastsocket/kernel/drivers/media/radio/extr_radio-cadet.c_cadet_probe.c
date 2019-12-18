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
struct cadet {int io; } ;

/* Variables and functions */
 int cadet_getfreq (struct cadet*) ; 
 int /*<<< orphan*/  cadet_setfreq (struct cadet*,int) ; 
 int /*<<< orphan*/  release_region (int,int) ; 
 scalar_t__ request_region (int,int,char*) ; 

__attribute__((used)) static void cadet_probe(struct cadet *dev)
{
	static int iovals[8] = { 0x330, 0x332, 0x334, 0x336, 0x338, 0x33a, 0x33c, 0x33e };
	int i;

	for (i = 0; i < 8; i++) {
		dev->io = iovals[i];
		if (request_region(dev->io, 2, "cadet-probe")) {
			cadet_setfreq(dev, 1410);
			if (cadet_getfreq(dev) == 1410) {
				release_region(dev->io, 2);
				return;
			}
			release_region(dev->io, 2);
		}
	}
	dev->io = -1;
}