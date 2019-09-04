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
typedef  int /*<<< orphan*/  u_char ;
struct mptcp_mpcapable_opt_common {int mmco_flags; } ;

/* Variables and functions */
 int MPCAP_BBIT ; 
 int MPCAP_CBIT ; 
 int MPCAP_DBIT ; 
 int MPCAP_EBIT ; 
 int MPCAP_FBIT ; 
 int MPCAP_GBIT ; 
 int MPCAP_PROPOSAL_SBIT ; 

__attribute__((used)) static int
mptcp_valid_mpcapable_common_opt(u_char *cp)
{
	struct mptcp_mpcapable_opt_common *rsp =
	    (struct mptcp_mpcapable_opt_common *)cp;

	/* mmco_kind, mmco_len and mmco_subtype are validated before */

	if (!(rsp->mmco_flags & MPCAP_PROPOSAL_SBIT))
		return (0);

	if (rsp->mmco_flags & (MPCAP_BBIT | MPCAP_CBIT | MPCAP_DBIT |
	    MPCAP_EBIT | MPCAP_FBIT | MPCAP_GBIT))
		return (0);

	return (1);
}