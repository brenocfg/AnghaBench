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
struct mpoa_client {int number_of_mps_macs; int /*<<< orphan*/ * mps_macs; } ;
struct k_message {int /*<<< orphan*/  MPS_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void set_mps_mac_addr_rcvd(struct k_message *msg, struct mpoa_client *client)
{

	if(client->number_of_mps_macs)
		kfree(client->mps_macs);
	client->number_of_mps_macs = 0;
	client->mps_macs = kmemdup(msg->MPS_ctrl, ETH_ALEN, GFP_KERNEL);
	if (client->mps_macs == NULL) {
		printk("mpoa: set_mps_mac_addr_rcvd: out of memory\n");
		return;
	}
	client->number_of_mps_macs = 1;

	return;
}