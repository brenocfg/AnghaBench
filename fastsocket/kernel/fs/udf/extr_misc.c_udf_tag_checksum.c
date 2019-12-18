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
typedef  scalar_t__ u8 ;
struct tag {int dummy; } ;

/* Variables and functions */

u8 udf_tag_checksum(const struct tag *t)
{
	u8 *data = (u8 *)t;
	u8 checksum = 0;
	int i;
	for (i = 0; i < sizeof(struct tag); ++i)
		if (i != 4) /* position of checksum */
			checksum += data[i];
	return checksum;
}