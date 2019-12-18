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
typedef  int u_long ;
struct TYPE_8__ {int /*<<< orphan*/ * s6_addr32; } ;
struct TYPE_7__ {TYPE_4__ sin6_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/ * s6_addr32; } ;
struct TYPE_6__ {TYPE_1__ sin6_addr; } ;
struct in6_addrpolicy {scalar_t__ label; scalar_t__ use; TYPE_3__ addrmask; TYPE_2__ addr; } ;
typedef  int /*<<< orphan*/  ent0 ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ ADDR_LABEL_NOTAPP ; 
 int EINVAL ; 
 int ENOTSUP ; 
 int EOPNOTSUPP ; 
#define  SIOCAADDRCTL_POLICY 129 
#define  SIOCDADDRCTL_POLICY 128 
 int add_addrsel_policyent (struct in6_addrpolicy*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,struct in6_addrpolicy*,int) ; 
 int delete_addrsel_policyent (struct in6_addrpolicy*) ; 
 scalar_t__ in6_mask2len (TYPE_4__*,int /*<<< orphan*/ *) ; 

int
in6_src_ioctl(u_long cmd, caddr_t data)
{
	int i;
	struct in6_addrpolicy ent0;

	if (cmd != SIOCAADDRCTL_POLICY && cmd != SIOCDADDRCTL_POLICY)
		return (EOPNOTSUPP); /* check for safety */

	bcopy(data, &ent0, sizeof (ent0));

	if (ent0.label == ADDR_LABEL_NOTAPP)
		return (EINVAL);
	/* check if the prefix mask is consecutive. */
	if (in6_mask2len(&ent0.addrmask.sin6_addr, NULL) < 0)
		return (EINVAL);
	/* clear trailing garbages (if any) of the prefix address. */
	for (i = 0; i < 4; i++) {
		ent0.addr.sin6_addr.s6_addr32[i] &=
			ent0.addrmask.sin6_addr.s6_addr32[i];
	}
	ent0.use = 0;

	switch (cmd) {
	case SIOCAADDRCTL_POLICY:
#ifdef ENABLE_ADDRSEL
		return (add_addrsel_policyent(&ent0));
#else
		return (ENOTSUP);
#endif
	case SIOCDADDRCTL_POLICY:
#ifdef ENABLE_ADDRSEL
		return (delete_addrsel_policyent(&ent0));
#else
		return (ENOTSUP);
#endif
	}

	return (0);		/* XXX: compromise compilers */
}