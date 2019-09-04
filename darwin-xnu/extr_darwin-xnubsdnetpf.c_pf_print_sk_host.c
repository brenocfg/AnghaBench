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
typedef  int /*<<< orphan*/  u_int8_t ;
struct TYPE_2__ {int /*<<< orphan*/  port; int /*<<< orphan*/  call_id; int /*<<< orphan*/  spi; } ;
struct pf_state_host {TYPE_1__ xport; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  sa_family_t ;

/* Variables and functions */
#define  IPPROTO_ESP 131 
#define  IPPROTO_GRE 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  PF_GRE_PPTP_VARIANT ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_print_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
pf_print_sk_host(struct pf_state_host *sh, sa_family_t af, int proto,
	u_int8_t proto_variant)
{
	pf_print_addr(&sh->addr, af);

	switch (proto) {
	case IPPROTO_ESP:
		if (sh->xport.spi)
			printf("[%08x]", ntohl(sh->xport.spi));
		break;

	case IPPROTO_GRE:
		if (proto_variant == PF_GRE_PPTP_VARIANT)
			printf("[%u]", ntohs(sh->xport.call_id));
		break;

	case IPPROTO_TCP:
	case IPPROTO_UDP:
		printf("[%u]", ntohs(sh->xport.port));
		break;

	default:
		break;
	}
}