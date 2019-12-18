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
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 scalar_t__ ETH_ALEN ; 
 size_t IFLA_ADDRESS ; 
 size_t IFLA_MACVLAN_MODE ; 
#define  MACVLAN_MODE_BRIDGE 131 
#define  MACVLAN_MODE_PASSTHRU 130 
#define  MACVLAN_MODE_PRIVATE 129 
#define  MACVLAN_MODE_VEPA 128 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int nla_get_u32 (struct nlattr*) ; 
 scalar_t__ nla_len (struct nlattr*) ; 

__attribute__((used)) static int macvlan_validate(struct nlattr *tb[], struct nlattr *data[])
{
	if (tb[IFLA_ADDRESS]) {
		if (nla_len(tb[IFLA_ADDRESS]) != ETH_ALEN)
			return -EINVAL;
		if (!is_valid_ether_addr(nla_data(tb[IFLA_ADDRESS])))
			return -EADDRNOTAVAIL;
	}

	if (data && data[IFLA_MACVLAN_MODE]) {
		switch (nla_get_u32(data[IFLA_MACVLAN_MODE])) {
		case MACVLAN_MODE_PRIVATE:
		case MACVLAN_MODE_VEPA:
		case MACVLAN_MODE_BRIDGE:
		case MACVLAN_MODE_PASSTHRU:
			break;
		default:
			return -EINVAL;
		}
	}
	return 0;
}