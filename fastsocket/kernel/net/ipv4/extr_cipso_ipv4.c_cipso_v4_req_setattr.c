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
typedef  int u32 ;
struct request_sock {int dummy; } ;
struct netlbl_lsm_secattr {int dummy; } ;
struct iphdr {int dummy; } ;
struct ip_options {int optlen; int cipso; int /*<<< orphan*/  __data; } ;
struct inet_request_sock {int /*<<< orphan*/  opt; } ;
struct cipso_v4_doi {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rcu; } ;

/* Variables and functions */
 int CIPSO_V4_OPT_LEN_MAX ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cipso_v4_genopt (unsigned char*,int,struct cipso_v4_doi const*,struct netlbl_lsm_secattr const*) ; 
 TYPE_1__* get_ip_options_rcu (struct ip_options*) ; 
 struct inet_request_sock* inet_rsk (struct request_sock*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 int /*<<< orphan*/  kfree_ip_options (struct ip_options*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct ip_options* kzalloc_ip_options (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  opt_kfree_rcu ; 
 struct ip_options* xchg (int /*<<< orphan*/ *,struct ip_options*) ; 

int cipso_v4_req_setattr(struct request_sock *req,
			 const struct cipso_v4_doi *doi_def,
			 const struct netlbl_lsm_secattr *secattr)
{
	int ret_val = -EPERM;
	unsigned char *buf = NULL;
	u32 buf_len;
	u32 opt_len;
	struct ip_options *opt = NULL;
	struct inet_request_sock *req_inet;

	/* We allocate the maximum CIPSO option size here so we are probably
	 * being a little wasteful, but it makes our life _much_ easier later
	 * on and after all we are only talking about 40 bytes. */
	buf_len = CIPSO_V4_OPT_LEN_MAX;
	buf = kmalloc(buf_len, GFP_ATOMIC);
	if (buf == NULL) {
		ret_val = -ENOMEM;
		goto req_setattr_failure;
	}

	ret_val = cipso_v4_genopt(buf, buf_len, doi_def, secattr);
	if (ret_val < 0)
		goto req_setattr_failure;
	buf_len = ret_val;

	/* We can't use ip_options_get() directly because it makes a call to
	 * ip_options_get_alloc() which allocates memory with GFP_KERNEL and
	 * we won't always have CAP_NET_RAW even though we _always_ want to
	 * set the IPOPT_CIPSO option. */
	opt_len = (buf_len + 3) & ~3;
	opt = kzalloc_ip_options(opt_len, GFP_ATOMIC);
	if (opt == NULL) {
		ret_val = -ENOMEM;
		goto req_setattr_failure;
	}
	memcpy(opt->__data, buf, buf_len);
	opt->optlen = opt_len;
	opt->cipso = sizeof(struct iphdr);
	kfree(buf);
	buf = NULL;

	req_inet = inet_rsk(req);
	opt = xchg(&req_inet->opt, opt);
	if (opt)
		call_rcu(&get_ip_options_rcu(opt)->rcu, opt_kfree_rcu);

	return 0;

req_setattr_failure:
	kfree(buf);
	kfree_ip_options(opt);
	return ret_val;
}