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
struct wbcir_data {int irdata_count; int irdata_error; int /*<<< orphan*/  irdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_irdata_bit(struct wbcir_data *data, int set)
{
	if (data->irdata_count >= sizeof(data->irdata) * 8) {
		data->irdata_error = 1;
		return;
	}

	if (set)
		__set_bit(data->irdata_count, data->irdata);
	data->irdata_count++;
}