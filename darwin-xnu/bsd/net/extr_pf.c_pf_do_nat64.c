#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct pf_state_key {scalar_t__ af_lan; TYPE_4__ ext_gwy; TYPE_3__ gwy; TYPE_2__ ext_lan; TYPE_1__ lan; } ;
struct pf_pdesc {scalar_t__ af; int /*<<< orphan*/  ndaddr; int /*<<< orphan*/  naddr; } ;
typedef  int /*<<< orphan*/  pbuf_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int PF_DROP ; 
 int pf_nat64_ipv4 (int /*<<< orphan*/ *,int,struct pf_pdesc*) ; 
 int pf_nat64_ipv6 (int /*<<< orphan*/ *,int,struct pf_pdesc*) ; 

__attribute__((used)) static int
pf_do_nat64(struct pf_state_key *sk, struct pf_pdesc *pd, pbuf_t *pbuf,
	    int off)
{
	if (pd->af == AF_INET) {
		if (pd->af != sk->af_lan) {
			pd->ndaddr = sk->lan.addr;
			pd->naddr = sk->ext_lan.addr;
		} else {
			pd->naddr = sk->gwy.addr;
			pd->ndaddr = sk->ext_gwy.addr;
		}
		return (pf_nat64_ipv4(pbuf, off, pd));
	}
	else if (pd->af == AF_INET6) {
		if (pd->af != sk->af_lan) {
			pd->ndaddr = sk->lan.addr;
			pd->naddr = sk->ext_lan.addr;
			} else {
				pd->naddr = sk->gwy.addr;
				pd->ndaddr = sk->ext_gwy.addr;
			}
			return (pf_nat64_ipv6(pbuf, off, pd));
	}
	return (PF_DROP);
}