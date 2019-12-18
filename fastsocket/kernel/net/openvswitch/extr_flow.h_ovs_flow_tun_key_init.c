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
struct ovs_key_ipv4_tunnel {int /*<<< orphan*/  tun_flags; int /*<<< orphan*/  ipv4_ttl; int /*<<< orphan*/  ipv4_tos; int /*<<< orphan*/  ipv4_dst; int /*<<< orphan*/  ipv4_src; int /*<<< orphan*/  tun_id; } ;
struct iphdr {int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int OVS_TUNNEL_KEY_SIZE ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void ovs_flow_tun_key_init(struct ovs_key_ipv4_tunnel *tun_key,
					 const struct iphdr *iph, __be64 tun_id,
					 __be16 tun_flags)
{
	tun_key->tun_id = tun_id;
	tun_key->ipv4_src = iph->saddr;
	tun_key->ipv4_dst = iph->daddr;
	tun_key->ipv4_tos = iph->tos;
	tun_key->ipv4_ttl = iph->ttl;
	tun_key->tun_flags = tun_flags;

	/* clear struct padding. */
	memset((unsigned char *) tun_key + OVS_TUNNEL_KEY_SIZE, 0,
	       sizeof(*tun_key) - OVS_TUNNEL_KEY_SIZE);
}