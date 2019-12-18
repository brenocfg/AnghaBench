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
typedef  int u_int8_t ;
struct mbuf {int m_len; } ;
typedef  scalar_t__ mbuf_t ;
typedef  int /*<<< orphan*/  ipfilter_t ;
typedef  int /*<<< orphan*/  ipf_pktopts_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  ipf_injectv4_out (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipf_injectv6_out (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 scalar_t__ m_mtod (struct mbuf*) ; 
 struct mbuf* m_pullup (struct mbuf*,int) ; 

errno_t
ipf_inject_output(
	mbuf_t data,
	ipfilter_t filter_ref,
	ipf_pktopts_t options)
{
	struct mbuf	*m = (struct mbuf *)data;
	u_int8_t	vers;
	errno_t		error = 0;

	/* Make one byte of the header contiguous in the mbuf */
	if (m->m_len < 1) {
		m = m_pullup(m, 1);
		if (m == NULL)
			goto done;
	}

	vers = (*(u_int8_t *)m_mtod(m)) >> 4;
	switch (vers) {
		case 4:
			error = ipf_injectv4_out(data, filter_ref, options);
			break;
#if INET6
		case 6:
			error = ipf_injectv6_out(data, filter_ref, options);
			break;
#endif
		default:
			m_freem(m);
			error = ENOTSUP;
			break;
	}

done:
	return (error);
}