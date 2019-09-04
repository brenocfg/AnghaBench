#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_short ;
struct ip6_fw_head {struct ip6_fw_chain* lh_first; } ;
struct TYPE_6__ {struct ip6_fw_chain* le_next; } ;
struct TYPE_4__ {char* name; } ;
struct TYPE_5__ {TYPE_1__ fu_via_if; } ;
struct ip6_fw_chain {long fw_pcnt; long fw_bcnt; scalar_t__ fw_number; struct ip6_fw_chain* rule; TYPE_3__ chain; TYPE_2__ fw_in_if; } ;
struct ip6_fw {long fw_pcnt; long fw_bcnt; scalar_t__ fw_number; struct ip6_fw* rule; TYPE_3__ chain; TYPE_2__ fw_in_if; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int /*<<< orphan*/  FREE (struct ip6_fw_chain*,int /*<<< orphan*/ ) ; 
 int IP6FW_IFNLEN ; 
 int /*<<< orphan*/  LIST_INSERT_AFTER (struct ip6_fw_chain*,struct ip6_fw_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (struct ip6_fw_head*,struct ip6_fw_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_IP6FW ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct ip6_fw_chain* _MALLOC (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (struct ip6_fw_chain*,struct ip6_fw_chain*,int) ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/  err_prefix ; 

__attribute__((used)) static int
add_entry6(struct ip6_fw_head *chainptr, struct ip6_fw *frwl)
{
	struct ip6_fw *ftmp = 0;
	struct ip6_fw_chain *fwc = 0, *fcp, *fcpl = 0;
	u_short nbr = 0;

	fwc = _MALLOC(sizeof *fwc, M_IP6FW, M_WAITOK);
	ftmp = _MALLOC(sizeof *ftmp, M_IP6FW, M_WAITOK);
	if (!fwc || !ftmp) {
		dprintf(("%s malloc said no\n", err_prefix));
		if (fwc)  FREE(fwc, M_IP6FW);
		if (ftmp) FREE(ftmp, M_IP6FW);
		return (ENOSPC);
	}

	bcopy(frwl, ftmp, sizeof(struct ip6_fw));
	ftmp->fw_in_if.fu_via_if.name[IP6FW_IFNLEN - 1] = '\0';
	ftmp->fw_pcnt = 0L;
	ftmp->fw_bcnt = 0L;
	fwc->rule = ftmp;
	
	if (!chainptr->lh_first) {
		LIST_INSERT_HEAD(chainptr, fwc, chain);
		return(0);
        } else if (ftmp->fw_number == (u_short)-1) {
		if (fwc)  FREE(fwc, M_IP6FW);
		if (ftmp) FREE(ftmp, M_IP6FW);
		dprintf(("%s bad rule number\n", err_prefix));
		return (EINVAL);
        }

	/* If entry number is 0, find highest numbered rule and add 100 */
	if (ftmp->fw_number == 0) {
		for (fcp = chainptr->lh_first; fcp; fcp = fcp->chain.le_next) {
			if (fcp->rule->fw_number != (u_short)-1)
				nbr = fcp->rule->fw_number;
			else
				break;
		}
		if (nbr < (u_short)-1 - 100)
			nbr += 100;
		ftmp->fw_number = nbr;
	}

	/* Got a valid number; now insert it, keeping the list ordered */
	for (fcp = chainptr->lh_first; fcp; fcp = fcp->chain.le_next) {
		if (fcp->rule->fw_number > ftmp->fw_number) {
			if (fcpl) {
				LIST_INSERT_AFTER(fcpl, fwc, chain);
			} else {
				LIST_INSERT_HEAD(chainptr, fwc, chain);
			}
			break;
		} else {
			fcpl = fcp;
		}
	}

	bcopy(ftmp, frwl, sizeof(struct ip6_fw));
	return (0);
}