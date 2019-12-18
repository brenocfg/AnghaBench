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
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static void __card_checksum(u16 *buff,u32 len,u16 *cs1,u16 *cs2)
{
	u32 i;
    *cs1 = 0;
	*cs2 = 0;
	len /= 2;
    for (i = 0; i < len; ++i) {
        *cs1 += buff[i];
        *cs2 += (buff[i] ^ 0xffff);
    }
    if (*cs1 == 0xffff) *cs1 = 0;
    if (*cs2 == 0xffff) *cs2 = 0;
}