#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int raid_devs; } ;
struct raid_set {TYPE_1__ set; } ;

/* Variables and functions */
 int chunk_pages (unsigned int) ; 

__attribute__((used)) static inline unsigned stripe_pages(struct raid_set *rs, unsigned io_size)
{
	return chunk_pages(io_size) * rs->set.raid_devs;
}