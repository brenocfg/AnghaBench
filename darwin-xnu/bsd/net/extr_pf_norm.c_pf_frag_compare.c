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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct pf_addr {int /*<<< orphan*/ * addr32; TYPE_1__ v4addr; } ;
struct pf_fragment {int fr_af; int fr_p; int fr_id; int fr_id6; struct pf_addr fr_dstx; struct pf_addr fr_srcx; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline int
pf_frag_compare(struct pf_fragment *a, struct pf_fragment *b)
{
	int	diff;

	if ((diff = a->fr_af - b->fr_af))
		return (diff);
	else if ((diff = a->fr_p - b->fr_p))
		return (diff);
	else {
		struct pf_addr *sa = &a->fr_srcx;
		struct pf_addr *sb = &b->fr_srcx;
		struct pf_addr *da = &a->fr_dstx;
		struct pf_addr *db = &b->fr_dstx;
		
		switch (a->fr_af) {
#ifdef INET
		case AF_INET:
			if ((diff = a->fr_id - b->fr_id))
				return (diff);
			else if (sa->v4addr.s_addr < sb->v4addr.s_addr)
				return (-1);
			else if (sa->v4addr.s_addr > sb->v4addr.s_addr)
				return (1);
			else if (da->v4addr.s_addr < db->v4addr.s_addr)
				return (-1);
			else if (da->v4addr.s_addr > db->v4addr.s_addr)
				return (1);
			break;
#endif
#ifdef INET6
		case AF_INET6:
			if ((diff = a->fr_id6 - b->fr_id6))
				return (diff);
			else if (sa->addr32[3] < sb->addr32[3])
				return (-1);
			else if (sa->addr32[3] > sb->addr32[3])
				return (1);
			else if (sa->addr32[2] < sb->addr32[2])
				return (-1);
			else if (sa->addr32[2] > sb->addr32[2])
				return (1);
			else if (sa->addr32[1] < sb->addr32[1])
				return (-1);
			else if (sa->addr32[1] > sb->addr32[1])
				return (1);
			else if (sa->addr32[0] < sb->addr32[0])
				return (-1);
			else if (sa->addr32[0] > sb->addr32[0])
				return (1);
			else if (da->addr32[3] < db->addr32[3])
				return (-1);
			else if (da->addr32[3] > db->addr32[3])
				return (1);
			else if (da->addr32[2] < db->addr32[2])
				return (-1);
			else if (da->addr32[2] > db->addr32[2])
				return (1);
			else if (da->addr32[1] < db->addr32[1])
				return (-1);
			else if (da->addr32[1] > db->addr32[1])
				return (1);
			else if (da->addr32[0] < db->addr32[0])
				return (-1);
			else if (da->addr32[0] > db->addr32[0])
				return (1);
			break;
#endif
		default:
			VERIFY(!0 && "only IPv4 and IPv6 supported!");
			break;
		}
	}
	return (0);
}