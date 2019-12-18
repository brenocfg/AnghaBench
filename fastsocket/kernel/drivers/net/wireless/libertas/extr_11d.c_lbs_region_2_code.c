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
struct TYPE_3__ {size_t code; int /*<<< orphan*/  region; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 size_t COUNTRY_CODE_LEN ; 
 int /*<<< orphan*/  memcmp (size_t*,int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__* region_code_mapping ; 
 size_t toupper (size_t) ; 

__attribute__((used)) static u8 lbs_region_2_code(u8 *region)
{
	u8 i;

	for (i = 0; i < COUNTRY_CODE_LEN && region[i]; i++)
		region[i] = toupper(region[i]);

	for (i = 0; i < ARRAY_SIZE(region_code_mapping); i++) {
		if (!memcmp(region, region_code_mapping[i].region,
			    COUNTRY_CODE_LEN))
			return (region_code_mapping[i].code);
	}

	/* default is US */
	return (region_code_mapping[0].code);
}