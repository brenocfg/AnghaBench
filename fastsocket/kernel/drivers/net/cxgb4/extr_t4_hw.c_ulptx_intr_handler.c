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
struct intr_info {int member_0; char* member_1; int member_2; int member_3; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
#define  PBL_BOUND_ERR_CH0 131 
#define  PBL_BOUND_ERR_CH1 130 
#define  PBL_BOUND_ERR_CH2 129 
#define  PBL_BOUND_ERR_CH3 128 
 int /*<<< orphan*/  ULP_TX_INT_CAUSE ; 
 int /*<<< orphan*/  t4_fatal_err (struct adapter*) ; 
 scalar_t__ t4_handle_intr_status (struct adapter*,int /*<<< orphan*/ ,struct intr_info const*) ; 

__attribute__((used)) static void ulptx_intr_handler(struct adapter *adapter)
{
	static const struct intr_info ulptx_intr_info[] = {
		{ PBL_BOUND_ERR_CH3, "ULPTX channel 3 PBL out of bounds", -1,
		  0 },
		{ PBL_BOUND_ERR_CH2, "ULPTX channel 2 PBL out of bounds", -1,
		  0 },
		{ PBL_BOUND_ERR_CH1, "ULPTX channel 1 PBL out of bounds", -1,
		  0 },
		{ PBL_BOUND_ERR_CH0, "ULPTX channel 0 PBL out of bounds", -1,
		  0 },
		{ 0xfffffff, "ULPTX parity error", -1, 1 },
		{ 0 }
	};

	if (t4_handle_intr_status(adapter, ULP_TX_INT_CAUSE, ulptx_intr_info))
		t4_fatal_err(adapter);
}