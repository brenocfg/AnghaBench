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
typedef  scalar_t__ u32 ;
struct vio_dring_state {scalar_t__ num_entries; } ;

/* Variables and functions */

__attribute__((used)) static u32 next_idx(u32 idx, struct vio_dring_state *dr)
{
	if (++idx == dr->num_entries)
		idx = 0;
	return idx;
}