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
typedef  int u16 ;
struct TYPE_3__ {int countryCode; int /*<<< orphan*/  isoName; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* allCountries ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static u16 ath_regd_find_country_by_name(char *alpha2)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(allCountries); i++) {
		if (!memcmp(allCountries[i].isoName, alpha2, 2))
			return allCountries[i].countryCode;
	}

	return -1;
}