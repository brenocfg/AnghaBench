#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct mpoa_client {int number_of_mps_macs; int /*<<< orphan*/ * mps_macs; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MPS_AND_MPC ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int const*,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const uint8_t *copy_macs(struct mpoa_client *mpc,
				const uint8_t *router_mac,
				const uint8_t *tlvs, uint8_t mps_macs,
				uint8_t device_type)
{
	int num_macs;
	num_macs = (mps_macs > 1) ? mps_macs : 1;

	if (mpc->number_of_mps_macs != num_macs) { /* need to reallocate? */
		if (mpc->number_of_mps_macs != 0) kfree(mpc->mps_macs);
		mpc->number_of_mps_macs = 0;
		mpc->mps_macs = kmalloc(num_macs*ETH_ALEN, GFP_KERNEL);
		if (mpc->mps_macs == NULL) {
			printk("mpoa: (%s) copy_macs: out of mem\n", mpc->dev->name);
			return NULL;
		}
	}
	memcpy(mpc->mps_macs, router_mac, ETH_ALEN);
	tlvs += 20; if (device_type == MPS_AND_MPC) tlvs += 20;
	if (mps_macs > 0)
		memcpy(mpc->mps_macs, tlvs, mps_macs*ETH_ALEN);
	tlvs += mps_macs*ETH_ALEN;
	mpc->number_of_mps_macs = num_macs;

	return tlvs;
}