#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_3__ {size_t code; size_t* region; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* region_code_mapping ; 

__attribute__((used)) static u8 *lbs_code_2_region(u8 code)
{
	u8 i;

	for (i = 0; i < ARRAY_SIZE(region_code_mapping); i++) {
		if (region_code_mapping[i].code == code)
			return (region_code_mapping[i].region);
	}
	/* default is US */
	return (region_code_mapping[0].region);
}