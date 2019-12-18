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
typedef  size_t u32 ;
struct vf_data_storage {int flags; int num_vf_mc_hashes; int /*<<< orphan*/ * vf_mc_hashes; } ;
struct e1000_hw {int dummy; } ;
struct igb_adapter {struct vf_data_storage* vf_data; struct e1000_hw hw; } ;

/* Variables and functions */
 size_t E1000_VF_SET_PROMISC_MULTICAST ; 
 int /*<<< orphan*/  E1000_VMOLR (size_t) ; 
 size_t E1000_VMOLR_MPME ; 
 size_t E1000_VMOLR_ROMPE ; 
 size_t E1000_VMOLR_ROPE ; 
 size_t E1000_VT_MSGINFO_MASK ; 
 int EINVAL ; 
 int IGB_VF_FLAG_MULTI_PROMISC ; 
 int IGB_VF_FLAG_UNI_PROMISC ; 
 int /*<<< orphan*/  igb_mta_set (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 size_t rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int igb_set_vf_promisc(struct igb_adapter *adapter, u32 *msgbuf, u32 vf)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 vmolr = rd32(E1000_VMOLR(vf));
	struct vf_data_storage *vf_data = &adapter->vf_data[vf];

	vf_data->flags &= ~(IGB_VF_FLAG_UNI_PROMISC |
			    IGB_VF_FLAG_MULTI_PROMISC);
	vmolr &= ~(E1000_VMOLR_ROPE | E1000_VMOLR_ROMPE | E1000_VMOLR_MPME);

	if (*msgbuf & E1000_VF_SET_PROMISC_MULTICAST) {
		vmolr |= E1000_VMOLR_MPME;
		vf_data->flags |= IGB_VF_FLAG_MULTI_PROMISC;
		*msgbuf &= ~E1000_VF_SET_PROMISC_MULTICAST;
	} else {
		/* if we have hashes and we are clearing a multicast promisc
		 * flag we need to write the hashes to the MTA as this step
		 * was previously skipped
		 */
		if (vf_data->num_vf_mc_hashes > 30) {
			vmolr |= E1000_VMOLR_MPME;
		} else if (vf_data->num_vf_mc_hashes) {
			int j;
			vmolr |= E1000_VMOLR_ROMPE;
			for (j = 0; j < vf_data->num_vf_mc_hashes; j++)
				igb_mta_set(hw, vf_data->vf_mc_hashes[j]);
		}
	}

	wr32(E1000_VMOLR(vf), vmolr);

	/* there are flags left unprocessed, likely not supported */
	if (*msgbuf & E1000_VT_MSGINFO_MASK)
		return -EINVAL;

	return 0;
}