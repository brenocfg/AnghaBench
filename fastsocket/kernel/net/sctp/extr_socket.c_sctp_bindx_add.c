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
typedef  union sctp_addr {int dummy; } sctp_addr ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
struct sock {int dummy; } ;
struct sctp_af {int /*<<< orphan*/  sockaddr_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SCTP_DEBUG_PRINTK (char*,struct sock*,struct sockaddr*,int) ; 
 int /*<<< orphan*/  sctp_bindx_rem (struct sock*,struct sockaddr*,int) ; 
 int sctp_do_bind (struct sock*,union sctp_addr*,int /*<<< orphan*/ ) ; 
 struct sctp_af* sctp_get_af_specific (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sctp_bindx_add(struct sock *sk, struct sockaddr *addrs, int addrcnt)
{
	int cnt;
	int retval = 0;
	void *addr_buf;
	struct sockaddr *sa_addr;
	struct sctp_af *af;

	SCTP_DEBUG_PRINTK("sctp_bindx_add (sk: %p, addrs: %p, addrcnt: %d)\n",
			  sk, addrs, addrcnt);

	addr_buf = addrs;
	for (cnt = 0; cnt < addrcnt; cnt++) {
		/* The list may contain either IPv4 or IPv6 address;
		 * determine the address length for walking thru the list.
		 */
		sa_addr = (struct sockaddr *)addr_buf;
		af = sctp_get_af_specific(sa_addr->sa_family);
		if (!af) {
			retval = -EINVAL;
			goto err_bindx_add;
		}

		retval = sctp_do_bind(sk, (union sctp_addr *)sa_addr,
				      af->sockaddr_len);

		addr_buf += af->sockaddr_len;

err_bindx_add:
		if (retval < 0) {
			/* Failed. Cleanup the ones that have been added */
			if (cnt > 0)
				sctp_bindx_rem(sk, addrs, cnt);
			return retval;
		}
	}

	return retval;
}