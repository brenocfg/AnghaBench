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
typedef  int /*<<< orphan*/  u8 ;
typedef  enum qeth_prot_versions { ____Placeholder_qeth_prot_versions } qeth_prot_versions ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ qeth_l3_string_to_ipaddr (char const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qeth_l3_parse_rxipe(const char *buf, enum qeth_prot_versions proto,
		 u8 *addr)
{
	if (qeth_l3_string_to_ipaddr(buf, proto, addr)) {
		return -EINVAL;
	}
	return 0;
}