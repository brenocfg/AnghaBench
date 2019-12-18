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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static inline void u16_to_u8array (uint8_t* item, int offset, uint16_t value) {
	item[offset]     = (uint8_t) value;
	item[offset + 1] = (uint8_t)(value >> 8);
}