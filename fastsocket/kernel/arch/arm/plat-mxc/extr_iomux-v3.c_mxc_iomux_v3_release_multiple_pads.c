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
struct pad_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mxc_iomux_v3_release_pad (struct pad_desc*) ; 

void mxc_iomux_v3_release_multiple_pads(struct pad_desc *pad_list, int count)
{
	struct pad_desc *p = pad_list;
	int i;

	for (i = 0; i < count; i++) {
		mxc_iomux_v3_release_pad(p);
		p++;
	}
}