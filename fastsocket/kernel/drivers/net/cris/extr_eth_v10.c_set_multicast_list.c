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
struct net_local {int /*<<< orphan*/  lock; } ;
struct net_device {int mc_count; int flags; struct dev_mc_list* mc_list; } ;
struct dev_mc_list {char* dmi_addr; struct dev_mc_list* next; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 unsigned long* R_NETWORK_GA_0 ; 
 unsigned long* R_NETWORK_GA_1 ; 
 int /*<<< orphan*/ * R_NETWORK_REC_CONFIG ; 
 int /*<<< orphan*/  SETS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  discard ; 
 int /*<<< orphan*/  individual ; 
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  network_rec_config_shadow ; 
 int /*<<< orphan*/  receive ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set_multicast_list(struct net_device *dev)
{
	struct net_local *lp = netdev_priv(dev);
	int num_addr = dev->mc_count;
	unsigned long int lo_bits;
	unsigned long int hi_bits;

	spin_lock(&lp->lock);
	if (dev->flags & IFF_PROMISC) {
		/* promiscuous mode */
		lo_bits = 0xfffffffful;
		hi_bits = 0xfffffffful;

		/* Enable individual receive */
		SETS(network_rec_config_shadow, R_NETWORK_REC_CONFIG, individual, receive);
		*R_NETWORK_REC_CONFIG = network_rec_config_shadow;
	} else if (dev->flags & IFF_ALLMULTI) {
		/* enable all multicasts */
		lo_bits = 0xfffffffful;
		hi_bits = 0xfffffffful;

		/* Disable individual receive */
		SETS(network_rec_config_shadow, R_NETWORK_REC_CONFIG, individual, discard);
		*R_NETWORK_REC_CONFIG =  network_rec_config_shadow;
	} else if (num_addr == 0) {
		/* Normal, clear the mc list */
		lo_bits = 0x00000000ul;
		hi_bits = 0x00000000ul;

		/* Disable individual receive */
		SETS(network_rec_config_shadow, R_NETWORK_REC_CONFIG, individual, discard);
		*R_NETWORK_REC_CONFIG =  network_rec_config_shadow;
	} else {
		/* MC mode, receive normal and MC packets */
		char hash_ix;
		struct dev_mc_list *dmi = dev->mc_list;
		int i;
		char *baddr;

		lo_bits = 0x00000000ul;
		hi_bits = 0x00000000ul;
		for (i = 0; i < num_addr; i++) {
			/* Calculate the hash index for the GA registers */

			hash_ix = 0;
			baddr = dmi->dmi_addr;
			hash_ix ^= (*baddr) & 0x3f;
			hash_ix ^= ((*baddr) >> 6) & 0x03;
			++baddr;
			hash_ix ^= ((*baddr) << 2) & 0x03c;
			hash_ix ^= ((*baddr) >> 4) & 0xf;
			++baddr;
			hash_ix ^= ((*baddr) << 4) & 0x30;
			hash_ix ^= ((*baddr) >> 2) & 0x3f;
			++baddr;
			hash_ix ^= (*baddr) & 0x3f;
			hash_ix ^= ((*baddr) >> 6) & 0x03;
			++baddr;
			hash_ix ^= ((*baddr) << 2) & 0x03c;
			hash_ix ^= ((*baddr) >> 4) & 0xf;
			++baddr;
			hash_ix ^= ((*baddr) << 4) & 0x30;
			hash_ix ^= ((*baddr) >> 2) & 0x3f;

			hash_ix &= 0x3f;

			if (hash_ix >= 32) {
				hi_bits |= (1 << (hash_ix-32));
			} else {
				lo_bits |= (1 << hash_ix);
			}
			dmi = dmi->next;
		}
		/* Disable individual receive */
		SETS(network_rec_config_shadow, R_NETWORK_REC_CONFIG, individual, discard);
		*R_NETWORK_REC_CONFIG = network_rec_config_shadow;
	}
	*R_NETWORK_GA_0 = lo_bits;
	*R_NETWORK_GA_1 = hi_bits;
	spin_unlock(&lp->lock);
}