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
typedef  size_t u32 ;
typedef  int u16 ;
struct brcm_rateset {size_t count; int* rates; } ;

/* Variables and functions */
 int BRCMS_RATE_FLAG ; 
 int BRCMS_RATE_MASK ; 

__attribute__((used)) static void brcms_set_basic_rate(struct brcm_rateset *rs, u16 rate, bool is_br)
{
	u32 i;

	for (i = 0; i < rs->count; i++) {
		if (rate != (rs->rates[i] & 0x7f))
			continue;

		if (is_br)
			rs->rates[i] |= BRCMS_RATE_FLAG;
		else
			rs->rates[i] &= BRCMS_RATE_MASK;
		return;
	}
}