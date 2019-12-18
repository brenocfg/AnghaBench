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
struct ricb {int flags; int /*<<< orphan*/ * ipv4_hash_key; int /*<<< orphan*/ * ipv6_hash_key; int /*<<< orphan*/  mask; int /*<<< orphan*/  base_cq; scalar_t__ hash_cq_id; } ;
struct ql_adapter {int rss_ring_count; int /*<<< orphan*/  ndev; struct ricb ricb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_LR ; 
 int /*<<< orphan*/  RSS_L4K ; 
 int RSS_L6K ; 
 int RSS_LB ; 
 int RSS_LI ; 
 int RSS_LM ; 
 int RSS_RT4 ; 
 int RSS_RT6 ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  memcpy (void*,int*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ql_write_cfg (struct ql_adapter*,struct ricb*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ql_start_rss(struct ql_adapter *qdev)
{
	u8 init_hash_seed[] = {0x6d, 0x5a, 0x56, 0xda, 0x25, 0x5b, 0x0e, 0xc2,
				0x41, 0x67, 0x25, 0x3d, 0x43, 0xa3, 0x8f,
				0xb0, 0xd0, 0xca, 0x2b, 0xcb, 0xae, 0x7b,
				0x30, 0xb4, 0x77, 0xcb, 0x2d, 0xa3, 0x80,
				0x30, 0xf2, 0x0c, 0x6a, 0x42, 0xb7, 0x3b,
				0xbe, 0xac, 0x01, 0xfa};
	struct ricb *ricb = &qdev->ricb;
	int status = 0;
	int i;
	u8 *hash_id = (u8 *) ricb->hash_cq_id;

	memset((void *)ricb, 0, sizeof(*ricb));

	ricb->base_cq = RSS_L4K;
	ricb->flags =
		(RSS_L6K | RSS_LI | RSS_LB | RSS_LM | RSS_RT4 | RSS_RT6);
	ricb->mask = cpu_to_le16((u16)(0x3ff));

	/*
	 * Fill out the Indirection Table.
	 */
	for (i = 0; i < 1024; i++)
		hash_id[i] = (i & (qdev->rss_ring_count - 1));

	memcpy((void *)&ricb->ipv6_hash_key[0], init_hash_seed, 40);
	memcpy((void *)&ricb->ipv4_hash_key[0], init_hash_seed, 16);

	status = ql_write_cfg(qdev, ricb, sizeof(*ricb), CFG_LR, 0);
	if (status) {
		netif_err(qdev, ifup, qdev->ndev, "Failed to load RICB.\n");
		return status;
	}
	return status;
}