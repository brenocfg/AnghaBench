#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; } ;
struct TYPE_8__ {int /*<<< orphan*/  inbytes; int /*<<< orphan*/  inpkts; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; TYPE_1__ ustats; } ;
struct ip_vs_dest {int flags; TYPE_5__* svc; TYPE_2__ stats; } ;
struct ip_vs_conn {struct ip_vs_dest* dest; } ;
struct TYPE_13__ {int /*<<< orphan*/  inbytes; int /*<<< orphan*/  inpkts; } ;
struct TYPE_14__ {int /*<<< orphan*/  lock; TYPE_6__ ustats; } ;
struct TYPE_10__ {int /*<<< orphan*/  inbytes; int /*<<< orphan*/  inpkts; } ;
struct TYPE_11__ {int /*<<< orphan*/  lock; TYPE_3__ ustats; } ;
struct TYPE_12__ {TYPE_4__ stats; } ;

/* Variables and functions */
 int IP_VS_DEST_F_AVAILABLE ; 
 TYPE_7__ ip_vs_stats ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
ip_vs_in_stats(struct ip_vs_conn *cp, struct sk_buff *skb)
{
	struct ip_vs_dest *dest = cp->dest;
	if (dest && (dest->flags & IP_VS_DEST_F_AVAILABLE)) {
		spin_lock(&dest->stats.lock);
		dest->stats.ustats.inpkts++;
		dest->stats.ustats.inbytes += skb->len;
		spin_unlock(&dest->stats.lock);

		spin_lock(&dest->svc->stats.lock);
		dest->svc->stats.ustats.inpkts++;
		dest->svc->stats.ustats.inbytes += skb->len;
		spin_unlock(&dest->svc->stats.lock);

		spin_lock(&ip_vs_stats.lock);
		ip_vs_stats.ustats.inpkts++;
		ip_vs_stats.ustats.inbytes += skb->len;
		spin_unlock(&ip_vs_stats.lock);
	}
}