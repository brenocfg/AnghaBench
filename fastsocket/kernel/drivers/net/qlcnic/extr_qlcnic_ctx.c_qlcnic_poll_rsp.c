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
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_CDRP_CRB_OFFSET ; 
 int /*<<< orphan*/  QLCNIC_CDRP_IS_RSP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLCNIC_CDRP_RSP_TIMEOUT ; 
 int QLCNIC_OS_CRB_RETRY_COUNT ; 
 int /*<<< orphan*/  QLCRD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static u32
qlcnic_poll_rsp(struct qlcnic_adapter *adapter)
{
	u32 rsp;
	int timeout = 0;

	do {
		/* give atleast 1ms for firmware to respond */
		mdelay(1);

		if (++timeout > QLCNIC_OS_CRB_RETRY_COUNT)
			return QLCNIC_CDRP_RSP_TIMEOUT;

		rsp = QLCRD32(adapter, QLCNIC_CDRP_CRB_OFFSET);
	} while (!QLCNIC_CDRP_IS_RSP(rsp));

	return rsp;
}