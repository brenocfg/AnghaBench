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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int u8 ;
typedef  int u32 ;
struct net_device {int name; } ;
struct mpoa_client {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int MPC ; 
 int MPS ; 
 int MPS_AND_MPC ; 
 int TLV_MPOA_DEVICE_TYPE ; 
 int* copy_macs (struct mpoa_client*,int const*,int const*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 struct mpoa_client* find_mpc_by_lec (struct net_device*) ; 
 int /*<<< orphan*/  mpoa_device_type_string (int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  send_set_mps_ctrl_addr (int const*,struct mpoa_client*) ; 

__attribute__((used)) static void lane2_assoc_ind(struct net_device *dev, const u8 *mac_addr,
			    const u8 *tlvs, u32 sizeoftlvs)
{
	uint32_t type;
	uint8_t length, mpoa_device_type, number_of_mps_macs;
	const uint8_t *end_of_tlvs;
	struct mpoa_client *mpc;

	mpoa_device_type = number_of_mps_macs = 0; /* silence gcc */
	dprintk("mpoa: (%s) lane2_assoc_ind: received TLV(s), ", dev->name);
	dprintk("total length of all TLVs %d\n", sizeoftlvs);
	mpc = find_mpc_by_lec(dev); /* Sampo-Fix: moved here from below */
	if (mpc == NULL) {
		printk("mpoa: (%s) lane2_assoc_ind: no mpc\n", dev->name);
		return;
	}
	end_of_tlvs = tlvs + sizeoftlvs;
	while (end_of_tlvs - tlvs >= 5) {
		type = (tlvs[0] << 24) | (tlvs[1] << 16) | (tlvs[2] << 8) | tlvs[3];
		length = tlvs[4];
		tlvs += 5;
		dprintk("    type 0x%x length %02x\n", type, length);
		if (tlvs + length > end_of_tlvs) {
			printk("TLV value extends past its buffer, aborting parse\n");
			return;
		}

		if (type == 0) {
			printk("mpoa: (%s) lane2_assoc_ind: TLV type was 0, returning\n", dev->name);
			return;
		}

		if (type != TLV_MPOA_DEVICE_TYPE) {
			tlvs += length;
			continue;  /* skip other TLVs */
		}
		mpoa_device_type = *tlvs++;
		number_of_mps_macs = *tlvs++;
		dprintk("mpoa: (%s) MPOA device type '%s', ", dev->name, mpoa_device_type_string(mpoa_device_type));
		if (mpoa_device_type == MPS_AND_MPC &&
		    length < (42 + number_of_mps_macs*ETH_ALEN)) { /* :) */
			printk("\nmpoa: (%s) lane2_assoc_ind: short MPOA Device Type TLV\n",
			       dev->name);
			continue;
		}
		if ((mpoa_device_type == MPS || mpoa_device_type == MPC)
		    && length < 22 + number_of_mps_macs*ETH_ALEN) {
			printk("\nmpoa: (%s) lane2_assoc_ind: short MPOA Device Type TLV\n",
				dev->name);
			continue;
		}
		if (mpoa_device_type != MPS && mpoa_device_type != MPS_AND_MPC) {
			dprintk("ignoring non-MPS device\n");
			if (mpoa_device_type == MPC) tlvs += 20;
			continue;  /* we are only interested in MPSs */
		}
		if (number_of_mps_macs == 0 && mpoa_device_type == MPS_AND_MPC) {
			printk("\nmpoa: (%s) lane2_assoc_ind: MPS_AND_MPC has zero MACs\n", dev->name);
			continue;  /* someone should read the spec */
		}
		dprintk("this MPS has %d MAC addresses\n", number_of_mps_macs);

		/* ok, now we can go and tell our daemon the control address of MPS */
		send_set_mps_ctrl_addr(tlvs, mpc);

		tlvs = copy_macs(mpc, mac_addr, tlvs, number_of_mps_macs, mpoa_device_type);
		if (tlvs == NULL) return;
	}
	if (end_of_tlvs - tlvs != 0)
		printk("mpoa: (%s) lane2_assoc_ind: ignoring %Zd bytes of trailing TLV carbage\n",
		       dev->name, end_of_tlvs - tlvs);
	return;
}