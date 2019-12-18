#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int supported_devices; int* mixer_reroute; int* levels; } ;
typedef  TYPE_1__ ad1848_info ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int ad1848_mixer_get(ad1848_info * devc, int dev)
{
	if (!((1 << dev) & devc->supported_devices))
		return -EINVAL;

	dev = devc->mixer_reroute[dev];

	return devc->levels[dev];
}