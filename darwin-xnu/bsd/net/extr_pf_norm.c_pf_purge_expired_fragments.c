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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ u_int32_t ;
struct pf_fragment {scalar_t__ fr_timeout; int fr_af; int /*<<< orphan*/  fr_id6; int /*<<< orphan*/  fr_id; } ;
struct TYPE_2__ {scalar_t__* timeout; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int BUFFER_FRAGMENTS (struct pf_fragment*) ; 
 int /*<<< orphan*/  DPFPRINTF (char*) ; 
 size_t PFTM_FRAG ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct pf_fragment* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  VM_KERNEL_ADDRPERM (struct pf_fragment*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_cachequeue ; 
 TYPE_1__ pf_default_rule ; 
 int /*<<< orphan*/  pf_fragqueue ; 
 int /*<<< orphan*/  pf_free_fragment (struct pf_fragment*) ; 
 scalar_t__ pf_time_second () ; 

void
pf_purge_expired_fragments(void)
{
	struct pf_fragment *frag;
	u_int32_t expire = pf_time_second() -
	    pf_default_rule.timeout[PFTM_FRAG];

	while ((frag = TAILQ_LAST(&pf_fragqueue, pf_fragqueue)) != NULL) {
		VERIFY(BUFFER_FRAGMENTS(frag));
		if (frag->fr_timeout > expire)
			break;

		switch (frag->fr_af) {
		case AF_INET:
		      DPFPRINTF(("expiring IPv4 %d(0x%llx) from queue.\n",
			  ntohs(frag->fr_id),
			  (uint64_t)VM_KERNEL_ADDRPERM(frag)));
		      break;
		case AF_INET6:
		      DPFPRINTF(("expiring IPv6 %d(0x%llx) from queue.\n",
			  ntohl(frag->fr_id6),
			  (uint64_t)VM_KERNEL_ADDRPERM(frag)));
		      break;
		default:
		      VERIFY(0 && "only IPv4 and IPv6 supported");
		      break;
		}
		pf_free_fragment(frag);
	}

	while ((frag = TAILQ_LAST(&pf_cachequeue, pf_cachequeue)) != NULL) {
		VERIFY(!BUFFER_FRAGMENTS(frag));
		if (frag->fr_timeout > expire)
			break;

		switch (frag->fr_af) {
		case AF_INET:
		      DPFPRINTF(("expiring IPv4 %d(0x%llx) from cache.\n",
			  ntohs(frag->fr_id),
			  (uint64_t)VM_KERNEL_ADDRPERM(frag)));
		      break;
		case AF_INET6:
		      DPFPRINTF(("expiring IPv6 %d(0x%llx) from cache.\n",
			  ntohl(frag->fr_id6),
			  (uint64_t)VM_KERNEL_ADDRPERM(frag)));
		      break;
		default:
		      VERIFY(0 && "only IPv4 and IPv6 supported");
		      break;
		}
		pf_free_fragment(frag);
		VERIFY(TAILQ_EMPTY(&pf_cachequeue) ||
		    TAILQ_LAST(&pf_cachequeue, pf_cachequeue) != frag);
	}
}