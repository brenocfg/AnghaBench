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
typedef  size_t u8 ;
struct iphdr {int dummy; } ;
struct ip_options {scalar_t__ srr; scalar_t__ rr; scalar_t__ ts; scalar_t__ router_alert; size_t cipso; unsigned char* __data; size_t optlen; } ;
struct TYPE_2__ {int /*<<< orphan*/  rcu; } ;

/* Variables and functions */
 scalar_t__ IPOPT_NOP ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* get_ip_options_rcu (struct ip_options*) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  opt_kfree_rcu ; 

int cipso_v4_delopt(struct ip_options **opt_ptr)
{
	int hdr_delta = 0;
	struct ip_options *opt = *opt_ptr;

	if (opt->srr || opt->rr || opt->ts || opt->router_alert) {
		u8 cipso_len;
		u8 cipso_off;
		unsigned char *cipso_ptr;
		int iter;
		int optlen_new;

		cipso_off = opt->cipso - sizeof(struct iphdr);
		cipso_ptr = &opt->__data[cipso_off];
		cipso_len = cipso_ptr[1];

		if (opt->srr > opt->cipso)
			opt->srr -= cipso_len;
		if (opt->rr > opt->cipso)
			opt->rr -= cipso_len;
		if (opt->ts > opt->cipso)
			opt->ts -= cipso_len;
		if (opt->router_alert > opt->cipso)
			opt->router_alert -= cipso_len;
		opt->cipso = 0;

		memmove(cipso_ptr, cipso_ptr + cipso_len,
			opt->optlen - cipso_off - cipso_len);

		/* determining the new total option length is tricky because of
		 * the padding necessary, the only thing i can think to do at
		 * this point is walk the options one-by-one, skipping the
		 * padding at the end to determine the actual option size and
		 * from there we can determine the new total option length */
		iter = 0;
		optlen_new = 0;
		while (iter < opt->optlen)
			if (opt->__data[iter] != IPOPT_NOP) {
				iter += opt->__data[iter + 1];
				optlen_new = iter;
			} else
				iter++;
		hdr_delta = opt->optlen;
		opt->optlen = (optlen_new + 3) & ~3;
		hdr_delta -= opt->optlen;
	} else {
		/* only the cipso option was present on the socket so we can
		 * remove the entire option struct */
		*opt_ptr = NULL;
		hdr_delta = opt->optlen;
		call_rcu(&get_ip_options_rcu(opt)->rcu, opt_kfree_rcu);
	}

	return hdr_delta;
}