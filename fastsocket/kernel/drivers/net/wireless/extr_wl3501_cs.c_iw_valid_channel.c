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
struct TYPE_3__ {int reg_domain; int min; int max; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* iw_channel_table ; 

__attribute__((used)) static int iw_valid_channel(int reg_domain, int channel)
{
	int i, rc = 0;

	for (i = 0; i < ARRAY_SIZE(iw_channel_table); i++)
		if (reg_domain == iw_channel_table[i].reg_domain) {
			rc = channel >= iw_channel_table[i].min &&
			     channel <= iw_channel_table[i].max;
			break;
		}
	return rc;
}