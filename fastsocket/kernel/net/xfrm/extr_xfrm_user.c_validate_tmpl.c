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
typedef  int u16 ;
struct xfrm_user_tmpl {int family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EINVAL ; 
 int XFRM_MAX_DEPTH ; 

__attribute__((used)) static int validate_tmpl(int nr, struct xfrm_user_tmpl *ut, u16 family)
{
	int i;

	if (nr > XFRM_MAX_DEPTH)
		return -EINVAL;

	for (i = 0; i < nr; i++) {
		/* We never validated the ut->family value, so many
		 * applications simply leave it at zero.  The check was
		 * never made and ut->family was ignored because all
		 * templates could be assumed to have the same family as
		 * the policy itself.  Now that we will have ipv4-in-ipv6
		 * and ipv6-in-ipv4 tunnels, this is no longer true.
		 */
		if (!ut[i].family)
			ut[i].family = family;

		switch (ut[i].family) {
		case AF_INET:
			break;
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
		case AF_INET6:
			break;
#endif
		default:
			return -EINVAL;
		}
	}

	return 0;
}