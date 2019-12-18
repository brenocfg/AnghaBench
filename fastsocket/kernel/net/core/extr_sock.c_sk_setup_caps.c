#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sock {int sk_route_caps; int /*<<< orphan*/  sk_gso_max_size; } ;
struct dst_entry {TYPE_3__* dev; scalar_t__ header_len; } ;
struct TYPE_6__ {int features; int /*<<< orphan*/  gso_max_size; } ;
struct TYPE_5__ {int /*<<< orphan*/  gso_max_segs; } ;
struct TYPE_4__ {int /*<<< orphan*/  sk_gso_max_segs; } ;

/* Variables and functions */
 int NETIF_F_GSO ; 
 int NETIF_F_GSO_MASK ; 
 int NETIF_F_GSO_SOFTWARE ; 
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_SG ; 
 int /*<<< orphan*/  __sk_dst_set (struct sock*,struct dst_entry*) ; 
 TYPE_2__* netdev_extended (TYPE_3__*) ; 
 scalar_t__ sk_can_gso (struct sock*) ; 
 TYPE_1__* sk_extended (struct sock*) ; 

void sk_setup_caps(struct sock *sk, struct dst_entry *dst)
{
	__sk_dst_set(sk, dst);
	sk->sk_route_caps = dst->dev->features;
	if (sk->sk_route_caps & NETIF_F_GSO)
		sk->sk_route_caps |= NETIF_F_GSO_SOFTWARE;
	if (sk_can_gso(sk)) {
		if (dst->header_len) {
			sk->sk_route_caps &= ~NETIF_F_GSO_MASK;
		} else {
			sk->sk_route_caps |= NETIF_F_SG | NETIF_F_HW_CSUM;
			sk->sk_gso_max_size = dst->dev->gso_max_size;
			sk_extended(sk)->sk_gso_max_segs = netdev_extended(dst->dev)->gso_max_segs;
		}
	}
}