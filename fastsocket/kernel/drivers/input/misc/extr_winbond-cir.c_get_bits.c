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
typedef  int u16 ;
struct wbcir_data {int irdata_count; int irdata_off; int irdata_error; int /*<<< orphan*/  irdata; } ;

/* Variables and functions */
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16
get_bits(struct wbcir_data *data, int count)
{
	u16 val = 0x0;

	if (data->irdata_count - data->irdata_off < count) {
		data->irdata_error = 1;
		return 0x0;
	}

	while (count > 0) {
		val <<= 1;
		if (test_bit(data->irdata_off, data->irdata))
			val |= 0x1;
		count--;
		data->irdata_off++;
	}

	return val;
}