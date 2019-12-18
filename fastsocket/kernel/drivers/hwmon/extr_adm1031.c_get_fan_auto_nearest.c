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
struct adm1031_data {scalar_t__*** chan_select_table; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t FAN_CHAN_FROM_REG (scalar_t__) ; 

__attribute__((used)) static int
get_fan_auto_nearest(struct adm1031_data *data,
		     int chan, u8 val, u8 reg, u8 * new_reg)
{
	int i;
	int first_match = -1, exact_match = -1;
	u8 other_reg_val =
	    (*data->chan_select_table)[FAN_CHAN_FROM_REG(reg)][chan ? 0 : 1];

	if (val == 0) {
		*new_reg = 0;
		return 0;
	}

	for (i = 0; i < 8; i++) {
		if ((val == (*data->chan_select_table)[i][chan]) &&
		    ((*data->chan_select_table)[i][chan ? 0 : 1] ==
		     other_reg_val)) {
			/* We found an exact match */
			exact_match = i;
			break;
		} else if (val == (*data->chan_select_table)[i][chan] &&
			   first_match == -1) {
			/* Save the first match in case of an exact match has
			 * not been found
			 */
			first_match = i;
		}
	}

	if (exact_match >= 0) {
		*new_reg = exact_match;
	} else if (first_match >= 0) {
		*new_reg = first_match;
	} else {
		return -EINVAL;
	}
	return 0;
}