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
typedef  int u64 ;
typedef  int /*<<< orphan*/  nasid_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int) ; 
 int REMOTE_HUB_L (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIO_ICE_PMI_TX_DYN_CREDIT_STAT_CB3 ; 
 int TIO_ICE_PMI_TX_DYN_CREDIT_STAT_CB3_CREDIT_CNT_MASK ; 

__attribute__((used)) static int bitstream_loaded(nasid_t nasid)
{
	u64 cx_credits;

	cx_credits = REMOTE_HUB_L(nasid, TIO_ICE_PMI_TX_DYN_CREDIT_STAT_CB3);
	cx_credits &= TIO_ICE_PMI_TX_DYN_CREDIT_STAT_CB3_CREDIT_CNT_MASK;
	DBG("cx_credits= 0x%lx\n", cx_credits);

	return (cx_credits == 0xf) ? 1 : 0;
}