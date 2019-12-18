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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 scalar_t__ BUS_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ II (int /*<<< orphan*/ ) ; 
 scalar_t__ II_IO ; 
 scalar_t__ II_MEM ; 
 scalar_t__ LL (int /*<<< orphan*/ ) ; 
 scalar_t__ LL_L1 ; 
 scalar_t__ LL_LG ; 
 scalar_t__ MEM_ERROR (int /*<<< orphan*/ ) ; 
 int R4 (int /*<<< orphan*/ ) ; 
#define  R4_DRD 132 
#define  R4_DWR 131 
#define  R4_EVICT 130 
#define  R4_RD 129 
#define  R4_SNOOP 128 
 scalar_t__ TT (int /*<<< orphan*/ ) ; 
 scalar_t__ TT_DATA ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 

__attribute__((used)) static bool f14h_dc_mce(u16 ec, u8 xec)
{
	u8 r4	 = R4(ec);
	bool ret = true;

	if (MEM_ERROR(ec)) {

		if (TT(ec) != TT_DATA || LL(ec) != LL_L1)
			return false;

		switch (r4) {
		case R4_DRD:
		case R4_DWR:
			pr_cont("Data/Tag parity error due to %s.\n",
				(r4 == R4_DRD ? "load/hw prf" : "store"));
			break;
		case R4_EVICT:
			pr_cont("Copyback parity error on a tag miss.\n");
			break;
		case R4_SNOOP:
			pr_cont("Tag parity error during snoop.\n");
			break;
		default:
			ret = false;
		}
	} else if (BUS_ERROR(ec)) {

		if ((II(ec) != II_MEM && II(ec) != II_IO) || LL(ec) != LL_LG)
			return false;

		pr_cont("System read data error on a ");

		switch (r4) {
		case R4_RD:
			pr_cont("TLB reload.\n");
			break;
		case R4_DWR:
			pr_cont("store.\n");
			break;
		case R4_DRD:
			pr_cont("load.\n");
			break;
		default:
			ret = false;
		}
	} else {
		ret = false;
	}

	return ret;
}