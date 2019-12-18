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
union nd_opts {int nd_opts_done; struct nd_opt_hdr* nd_opts_search; struct nd_opt_hdr* nd_opts_last; } ;
typedef  int /*<<< orphan*/  u_char ;
struct nd_opt_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (union nd_opts*,int) ; 

void
nd6_option_init(void *opt, int icmp6len, union nd_opts *ndopts)
{
	bzero(ndopts, sizeof (*ndopts));
	ndopts->nd_opts_search = (struct nd_opt_hdr *)opt;
	ndopts->nd_opts_last =
	    (struct nd_opt_hdr *)(((u_char *)opt) + icmp6len);

	if (icmp6len == 0) {
		ndopts->nd_opts_done = 1;
		ndopts->nd_opts_search = NULL;
	}
}