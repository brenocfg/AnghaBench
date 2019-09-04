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
typedef  scalar_t__ u_short ;
struct ip6_fw_head {struct ip6_fw_chain* lh_first; } ;
struct TYPE_2__ {struct ip6_fw_chain* le_next; } ;
struct ip6_fw_chain {scalar_t__ fw_number; struct ip6_fw_chain* rule; TYPE_1__ chain; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FREE (struct ip6_fw_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct ip6_fw_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_IP6FW ; 
 int /*<<< orphan*/  chain ; 

__attribute__((used)) static int
del_entry6(struct ip6_fw_head *chainptr, u_short number)
{
	struct ip6_fw_chain *fcp;

	fcp = chainptr->lh_first;
	if (number != (u_short)-1) {
		for (; fcp; fcp = fcp->chain.le_next) {
			if (fcp->rule->fw_number == number) {
				LIST_REMOVE(fcp, chain);
				FREE(fcp->rule, M_IP6FW);
				FREE(fcp, M_IP6FW);
				return 0;
			}
		}
	}

	return (EINVAL);
}