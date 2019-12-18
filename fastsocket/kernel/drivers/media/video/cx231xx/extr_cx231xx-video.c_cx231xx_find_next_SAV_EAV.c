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
typedef  int u32 ;

/* Variables and functions */

u8 cx231xx_find_next_SAV_EAV(u8 *p_buffer, u32 buffer_size, u32 *p_bytes_used)
{
	u32 i;
	u8 sav_eav = 0;

	/*
	 * Don't search if the buffer size is less than 4.  It causes a page
	 * fault since buffer_size - 4 evaluates to a large number in that
	 * case.
	 */
	if (buffer_size < 4) {
		*p_bytes_used = buffer_size;
		return 0;
	}

	for (i = 0; i < (buffer_size - 3); i++) {

		if ((p_buffer[i] == 0xFF) &&
		    (p_buffer[i + 1] == 0x00) && (p_buffer[i + 2] == 0x00)) {

			*p_bytes_used = i + 4;
			sav_eav = p_buffer[i + 3];
			return sav_eav;
		}
	}

	*p_bytes_used = buffer_size;
	return 0;
}