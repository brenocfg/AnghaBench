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
struct pfi_kif {char* pfik_name; } ;
struct pf_state_key {int proto; int /*<<< orphan*/  proto_variant; int /*<<< orphan*/  af_gwy; int /*<<< orphan*/  ext_gwy; int /*<<< orphan*/  af_lan; int /*<<< orphan*/  ext_lan; int /*<<< orphan*/  gwy; int /*<<< orphan*/  lan; } ;
struct pf_state {int sync_flags; struct pf_state_key* state_key; } ;
struct TYPE_2__ {scalar_t__ debug; } ;

/* Variables and functions */
#define  IPPROTO_ICMP 131 
#define  IPPROTO_ICMPV6 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int PFSTATE_FROMSYNC ; 
 scalar_t__ PF_DEBUG_MISC ; 
 int /*<<< orphan*/  pf_print_sk_host (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ pf_status ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
pf_stateins_err(const char *tree, struct pf_state *s, struct pfi_kif *kif)
{
	struct pf_state_key	*sk = s->state_key;

	if (pf_status.debug >= PF_DEBUG_MISC) {
		printf("pf: state insert failed: %s %s ", tree, kif->pfik_name);
		switch (sk->proto) {
		case IPPROTO_TCP:
			printf("TCP");
			break;
		case IPPROTO_UDP:
			printf("UDP");
			break;
		case IPPROTO_ICMP:
			printf("ICMP4");
			break;
		case IPPROTO_ICMPV6:
			printf("ICMP6");
			break;
		default:
			printf("PROTO=%u", sk->proto);
			break;
		}
		printf(" lan: ");
		pf_print_sk_host(&sk->lan, sk->af_lan, sk->proto,
		    sk->proto_variant);
		printf(" gwy: ");
		pf_print_sk_host(&sk->gwy, sk->af_gwy, sk->proto,
		    sk->proto_variant);
		printf(" ext_lan: ");
		pf_print_sk_host(&sk->ext_lan, sk->af_lan, sk->proto,
		    sk->proto_variant);
		printf(" ext_gwy: ");
		pf_print_sk_host(&sk->ext_gwy, sk->af_gwy, sk->proto,
		    sk->proto_variant);
		if (s->sync_flags & PFSTATE_FROMSYNC)
			printf(" (from sync)");
		printf("\n");
	}
}