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
struct sci_sas_address {scalar_t__ high; scalar_t__ low; } ;
typedef  int s32 ;

/* Variables and functions */

__attribute__((used)) static s32 sci_sas_address_compare(
	struct sci_sas_address address_one,
	struct sci_sas_address address_two)
{
	if (address_one.high > address_two.high) {
		return 1;
	} else if (address_one.high < address_two.high) {
		return -1;
	} else if (address_one.low > address_two.low) {
		return 1;
	} else if (address_one.low < address_two.low) {
		return -1;
	}

	/* The two SAS Address must be identical */
	return 0;
}