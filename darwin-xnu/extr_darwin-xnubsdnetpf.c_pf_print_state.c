#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pf_state_key {int proto; int proto_variant; int /*<<< orphan*/  af_gwy; int /*<<< orphan*/  ext_gwy; int /*<<< orphan*/  af_lan; int /*<<< orphan*/  ext_lan; int /*<<< orphan*/  gwy; int /*<<< orphan*/  lan; } ;
struct TYPE_4__ {int wscale; int seqlo; int seqhi; int max_win; int seqdiff; int state; } ;
struct TYPE_3__ {int seqlo; int seqhi; int max_win; int seqdiff; int wscale; int state; } ;
struct pf_state {TYPE_2__ dst; TYPE_1__ src; struct pf_state_key* state_key; } ;

/* Variables and functions */
#define  IPPROTO_ESP 133 
#define  IPPROTO_GRE 132 
#define  IPPROTO_ICMP 131 
#define  IPPROTO_ICMPV6 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int PF_WSCALE_MASK ; 
 int /*<<< orphan*/  pf_print_sk_host (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
pf_print_state(struct pf_state *s)
{
	struct pf_state_key *sk = s->state_key;
	switch (sk->proto) {
	case IPPROTO_ESP:
		printf("ESP ");
		break;
	case IPPROTO_GRE:
		printf("GRE%u ", sk->proto_variant);
		break;
	case IPPROTO_TCP:
		printf("TCP ");
		break;
	case IPPROTO_UDP:
		printf("UDP ");
		break;
	case IPPROTO_ICMP:
		printf("ICMP ");
		break;
	case IPPROTO_ICMPV6:
		printf("ICMPV6 ");
		break;
	default:
		printf("%u ", sk->proto);
		break;
	}
	pf_print_sk_host(&sk->lan, sk->af_lan, sk->proto, sk->proto_variant);
	printf(" ");
	pf_print_sk_host(&sk->gwy, sk->af_gwy, sk->proto, sk->proto_variant);
	printf(" ");
	pf_print_sk_host(&sk->ext_lan, sk->af_lan, sk->proto,
			 sk->proto_variant);
	printf(" ");
	pf_print_sk_host(&sk->ext_gwy, sk->af_gwy, sk->proto,
			 sk->proto_variant);
	printf(" [lo=%u high=%u win=%u modulator=%u", s->src.seqlo,
	    s->src.seqhi, s->src.max_win, s->src.seqdiff);
	if (s->src.wscale && s->dst.wscale)
		printf(" wscale=%u", s->src.wscale & PF_WSCALE_MASK);
	printf("]");
	printf(" [lo=%u high=%u win=%u modulator=%u", s->dst.seqlo,
	    s->dst.seqhi, s->dst.max_win, s->dst.seqdiff);
	if (s->src.wscale && s->dst.wscale)
		printf(" wscale=%u", s->dst.wscale & PF_WSCALE_MASK);
	printf("]");
	printf(" %u:%u", s->src.state, s->dst.state);
}