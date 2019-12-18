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

/* Variables and functions */
 int at93c_read_databit () ; 

__attribute__((used)) static u8 at93c_read_byte(void)
{
	int i;
	u8 data = 0;

	for (i = 0; i <= 7; i++) {
		data <<= 1;
		data |= at93c_read_databit();
	}
	return data;
}