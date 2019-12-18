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
typedef  int u8 ;
typedef  int u16 ;
struct wbcir_data {int irdata_error; } ;

/* Variables and functions */
 int get_bits (struct wbcir_data*,int) ; 

__attribute__((used)) static u8
wbcir_rc6cells_to_byte(struct wbcir_data *data)
{
	u16 raw = get_bits(data, 16);
	u8 val = 0x00;
	int bit;

	for (bit = 0; bit < 8; bit++) {
		switch (raw & 0x03) {
		case 0x01:
			break;
		case 0x02:
			val |= (0x01 << bit);
			break;
		default:
			data->irdata_error = 1;
			break;
		}
		raw >>= 2;
	}

	return val;
}