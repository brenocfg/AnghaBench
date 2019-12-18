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

/* Variables and functions */
 int /*<<< orphan*/  ACT2000_PORTLEN ; 
 int /*<<< orphan*/  ISA_REGION ; 
 int act2000_isa_reset (unsigned short) ; 
 int /*<<< orphan*/  release_region (unsigned short,int /*<<< orphan*/ ) ; 
 scalar_t__ request_region (unsigned short,int /*<<< orphan*/ ,char*) ; 

int
act2000_isa_detect(unsigned short portbase)
{
        int ret = 0;

	if (request_region(portbase, ACT2000_PORTLEN, "act2000isa")) {
                ret = act2000_isa_reset(portbase);
		release_region(portbase, ISA_REGION);
	}
        return ret;
}