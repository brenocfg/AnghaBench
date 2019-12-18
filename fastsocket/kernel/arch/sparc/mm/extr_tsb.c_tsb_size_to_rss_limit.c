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
struct tsb {int dummy; } ;

/* Variables and functions */
 unsigned long sysctl_tsb_ratio ; 

__attribute__((used)) static unsigned long tsb_size_to_rss_limit(unsigned long new_size)
{
	unsigned long num_ents = (new_size / sizeof(struct tsb));

	if (sysctl_tsb_ratio < 0)
		return num_ents - (num_ents >> -sysctl_tsb_ratio);
	else
		return num_ents + (num_ents >> sysctl_tsb_ratio);
}