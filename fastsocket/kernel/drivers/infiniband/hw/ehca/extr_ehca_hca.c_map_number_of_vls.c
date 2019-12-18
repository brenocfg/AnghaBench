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
struct ehca_shca {int /*<<< orphan*/  ib_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ehca_err (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static u8 map_number_of_vls(struct ehca_shca *shca, u32 vl_cap)
{
	switch (vl_cap) {
	case 0x1:
		return 1;
	case 0x2:
		return 2;
	case 0x3:
		return 4;
	case 0x4:
		return 8;
	case 0x5:
		return 15;
	default:
		ehca_err(&shca->ib_device, "invalid Vl Capability: %x.",
			 vl_cap);
		return 0;
	}
}