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
typedef  int /*<<< orphan*/  u32 ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 size_t IFLA_AF_SPEC ; 
 size_t IFLA_EXT_MASK ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 

__attribute__((used)) static u32 get_ext_mask(struct nlattr *tb[])
{
	if (tb[IFLA_EXT_MASK])
		return nla_get_u32(tb[IFLA_EXT_MASK]);

	/* RHEL6 HACK
	 *
	 * IFLA_EXT_MASK did not match the upstream definition in
	 * RHEL6.4. This was corrected in RHEL6.5. The following
	 * provides backwards compatibility with binaries that were
	 * compiled against RHEL6.4.
	 *
	 * The following is valid because IFLA_EXT_MASK is never
	 * used in combination with the conflicting IFLA_AF_SPEC.
	 */
	if (tb[IFLA_AF_SPEC] && nla_len(tb[IFLA_AF_SPEC]) == 4)
		return nla_get_u32(tb[IFLA_AF_SPEC]);

	return 0;
}