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
typedef  int u16 ;
struct sock {int dummy; } ;
struct netlbl_lsm_secattr {int /*<<< orphan*/  domain; } ;
struct TYPE_2__ {int /*<<< orphan*/  cipsov4; } ;
struct netlbl_dom_map {TYPE_1__ type_def; int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  AF_INET 132 
#define  AF_INET6 131 
 int EDESTADDRREQ ; 
 int ENOENT ; 
 int EPROTONOSUPPORT ; 
#define  NETLBL_NLTYPE_ADDRSELECT 130 
#define  NETLBL_NLTYPE_CIPSOV4 129 
#define  NETLBL_NLTYPE_UNLABELED 128 
 int cipso_v4_sock_setattr (struct sock*,int /*<<< orphan*/ ,struct netlbl_lsm_secattr const*) ; 
 struct netlbl_dom_map* netlbl_domhsh_getentry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int netlbl_sock_setattr(struct sock *sk,
			u16 family,
			const struct netlbl_lsm_secattr *secattr)
{
	int ret_val;
	struct netlbl_dom_map *dom_entry;

	rcu_read_lock();
	dom_entry = netlbl_domhsh_getentry(secattr->domain);
	if (dom_entry == NULL) {
		ret_val = -ENOENT;
		goto socket_setattr_return;
	}
	switch (family) {
	case AF_INET:
		switch (dom_entry->type) {
		case NETLBL_NLTYPE_ADDRSELECT:
			ret_val = -EDESTADDRREQ;
			break;
		case NETLBL_NLTYPE_CIPSOV4:
			ret_val = cipso_v4_sock_setattr(sk,
						    dom_entry->type_def.cipsov4,
						    secattr);
			break;
		case NETLBL_NLTYPE_UNLABELED:
			ret_val = 0;
			break;
		default:
			ret_val = -ENOENT;
		}
		break;
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
	case AF_INET6:
		/* since we don't support any IPv6 labeling protocols right
		 * now we can optimize everything away until we do */
		ret_val = 0;
		break;
#endif /* IPv6 */
	default:
		ret_val = -EPROTONOSUPPORT;
	}

socket_setattr_return:
	rcu_read_unlock();
	return ret_val;
}