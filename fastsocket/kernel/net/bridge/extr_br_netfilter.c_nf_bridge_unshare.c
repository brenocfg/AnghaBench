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
struct sk_buff {struct nf_bridge_info* nf_bridge; } ;
struct nf_bridge_info {int /*<<< orphan*/  use; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (struct nf_bridge_info*,struct nf_bridge_info*,int) ; 
 struct nf_bridge_info* nf_bridge_alloc (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_bridge_put (struct nf_bridge_info*) ; 

__attribute__((used)) static inline struct nf_bridge_info *nf_bridge_unshare(struct sk_buff *skb)
{
	struct nf_bridge_info *nf_bridge = skb->nf_bridge;

	if (atomic_read(&nf_bridge->use) > 1) {
		struct nf_bridge_info *tmp = nf_bridge_alloc(skb);

		if (tmp) {
			memcpy(tmp, nf_bridge, sizeof(struct nf_bridge_info));
			atomic_set(&tmp->use, 1);
			nf_bridge_put(nf_bridge);
		}
		nf_bridge = tmp;
	}
	return nf_bridge;
}