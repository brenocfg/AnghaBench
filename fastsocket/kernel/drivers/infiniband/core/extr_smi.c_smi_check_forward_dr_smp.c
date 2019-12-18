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
struct ib_smp {int hop_ptr; int hop_cnt; scalar_t__ dr_dlid; scalar_t__ dr_slid; } ;
typedef  enum smi_forward_action { ____Placeholder_smi_forward_action } smi_forward_action ;

/* Variables and functions */
 scalar_t__ IB_LID_PERMISSIVE ; 
 int IB_SMI_FORWARD ; 
 int IB_SMI_LOCAL ; 
 int IB_SMI_SEND ; 
 int /*<<< orphan*/  ib_get_smp_direction (struct ib_smp*) ; 

enum smi_forward_action smi_check_forward_dr_smp(struct ib_smp *smp)
{
	u8 hop_ptr, hop_cnt;

	hop_ptr = smp->hop_ptr;
	hop_cnt = smp->hop_cnt;

	if (!ib_get_smp_direction(smp)) {
		/* C14-9:2 -- intermediate hop */
		if (hop_ptr && hop_ptr < hop_cnt)
			return IB_SMI_FORWARD;

		/* C14-9:3 -- at the end of the DR segment of path */
		if (hop_ptr == hop_cnt)
			return (smp->dr_dlid == IB_LID_PERMISSIVE ?
				IB_SMI_SEND : IB_SMI_LOCAL);

		/* C14-9:4 -- hop_ptr = hop_cnt + 1 -> give to SMA/SM */
		if (hop_ptr == hop_cnt + 1)
			return IB_SMI_SEND;
	} else {
		/* C14-13:2  -- intermediate hop */
		if (2 <= hop_ptr && hop_ptr <= hop_cnt)
			return IB_SMI_FORWARD;

		/* C14-13:3 -- at the end of the DR segment of path */
		if (hop_ptr == 1)
			return (smp->dr_slid != IB_LID_PERMISSIVE ?
				IB_SMI_SEND : IB_SMI_LOCAL);
	}
	return IB_SMI_LOCAL;
}