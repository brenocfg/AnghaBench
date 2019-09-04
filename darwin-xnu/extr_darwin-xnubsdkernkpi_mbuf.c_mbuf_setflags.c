#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mbuf_t ;
typedef  int mbuf_flags_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_4__ {int m_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  m_reinit (TYPE_1__*,int) ; 
 int mbuf_cflags_mask ; 
 int mbuf_flags_mask ; 

errno_t
mbuf_setflags(mbuf_t mbuf, mbuf_flags_t flags)
{
	errno_t ret = 0;
	mbuf_flags_t oflags = mbuf->m_flags;

	/*
	 * 1. Return error if public but un-alterable flags are changed
	 *    in flags argument.
	 * 2. Return error if bits other than public flags are set in passed
	 *    flags argument.
	 *    Please note that private flag bits must be passed as reset by
	 *    kexts, as they must use mbuf_flags KPI to get current set of
	 *    mbuf flags and mbuf_flags KPI does not expose private flags.
	 */
	if ((flags ^ oflags) & mbuf_cflags_mask) {
		ret = EINVAL;
	} else if (flags & ~mbuf_flags_mask) {
		ret = EINVAL;
	} else {
		mbuf->m_flags = flags | (mbuf->m_flags & ~mbuf_flags_mask);
		/*
		 * If M_PKTHDR bit has changed, we have work to do;
		 * m_reinit() will take care of setting/clearing the
		 * bit, as well as the rest of bookkeeping.
		 */
		if ((oflags ^ mbuf->m_flags) & M_PKTHDR) {
			mbuf->m_flags ^= M_PKTHDR;	/* restore */
			ret = m_reinit(mbuf,
			    (mbuf->m_flags & M_PKTHDR) ? 0 : 1);
		}
	}

	return (ret);
}