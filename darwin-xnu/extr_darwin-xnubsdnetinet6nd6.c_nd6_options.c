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
union nd_opts {scalar_t__ nd_opts_done; struct nd_opt_prefix_info* nd_opts_pi_end; struct nd_opt_hdr** nd_opt_array; int /*<<< orphan*/ * nd_opts_last; int /*<<< orphan*/ * nd_opts_search; } ;
struct nd_opt_prefix_info {int dummy; } ;
struct nd_opt_hdr {int nd_opt_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  icp6s_nd_toomanyopt; int /*<<< orphan*/  icp6s_nd_badopt; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_INFO ; 
#define  ND_OPT_DNSSL 135 
#define  ND_OPT_MTU 134 
#define  ND_OPT_NONCE 133 
#define  ND_OPT_PREFIX_INFORMATION 132 
#define  ND_OPT_RDNSS 131 
#define  ND_OPT_REDIRECTED_HEADER 130 
#define  ND_OPT_SOURCE_LINKADDR 129 
#define  ND_OPT_TARGET_LINKADDR 128 
 int /*<<< orphan*/  bzero (union nd_opts*,int) ; 
 TYPE_1__ icmp6stat ; 
 int nd6_maxndopt ; 
 struct nd_opt_hdr* nd6_option (union nd_opts*) ; 
 int /*<<< orphan*/  nd6log (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

int
nd6_options(union nd_opts *ndopts)
{
	struct nd_opt_hdr *nd_opt;
	int i = 0;

	if (ndopts == NULL)
		panic("ndopts == NULL in nd6_options");
	if (ndopts->nd_opts_last == NULL)
		panic("uninitialized ndopts in nd6_options");
	if (ndopts->nd_opts_search == NULL)
		return (0);

	while (1) {
		nd_opt = nd6_option(ndopts);
		if (nd_opt == NULL && ndopts->nd_opts_last == NULL) {
			/*
			 * Message validation requires that all included
			 * options have a length that is greater than zero.
			 */
			icmp6stat.icp6s_nd_badopt++;
			bzero(ndopts, sizeof (*ndopts));
			return (-1);
		}

		if (nd_opt == NULL)
			goto skip1;

		switch (nd_opt->nd_opt_type) {
		case ND_OPT_SOURCE_LINKADDR:
		case ND_OPT_TARGET_LINKADDR:
		case ND_OPT_MTU:
		case ND_OPT_REDIRECTED_HEADER:
		case ND_OPT_NONCE:
			if (ndopts->nd_opt_array[nd_opt->nd_opt_type]) {
				nd6log((LOG_INFO,
				    "duplicated ND6 option found (type=%d)\n",
				    nd_opt->nd_opt_type));
				/* XXX bark? */
			} else {
				ndopts->nd_opt_array[nd_opt->nd_opt_type] =
				    nd_opt;
			}
			break;
		case ND_OPT_PREFIX_INFORMATION:
			if (ndopts->nd_opt_array[nd_opt->nd_opt_type] == 0) {
				ndopts->nd_opt_array[nd_opt->nd_opt_type] =
				    nd_opt;
			}
			ndopts->nd_opts_pi_end =
			    (struct nd_opt_prefix_info *)nd_opt;
			break;
		case ND_OPT_RDNSS:
		case ND_OPT_DNSSL:
			/* ignore */
			break;
		default:
			/*
			 * Unknown options must be silently ignored,
			 * to accomodate future extension to the protocol.
			 */
			nd6log((LOG_DEBUG,
			    "nd6_options: unsupported option %d - "
			    "option ignored\n", nd_opt->nd_opt_type));
		}

skip1:
		i++;
		if (i > nd6_maxndopt) {
			icmp6stat.icp6s_nd_toomanyopt++;
			nd6log((LOG_INFO, "too many loop in nd opt\n"));
			break;
		}

		if (ndopts->nd_opts_done)
			break;
	}

	return (0);
}