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
struct sh_mobile_i2c_data {int pos; TYPE_1__* msg; } ;
struct TYPE_2__ {int len; } ;

/* Variables and functions */

__attribute__((used)) static int sh_mobile_i2c_is_last_byte(struct sh_mobile_i2c_data *pd)
{
	if (pd->pos == (pd->msg->len - 1))
		return 1;

	return 0;
}