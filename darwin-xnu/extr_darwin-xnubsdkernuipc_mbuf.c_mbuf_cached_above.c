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
typedef  int mbuf_class_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int MCR_COMP ; 
#define  MC_16KCL 134 
#define  MC_BIGCL 133 
#define  MC_CL 132 
#define  MC_MBUF 131 
#define  MC_MBUF_16KCL 130 
#define  MC_MBUF_BIGCL 129 
#define  MC_MBUF_CL 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_cache (int) ; 
 int /*<<< orphan*/  mcache_bkt_isempty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
mbuf_cached_above(mbuf_class_t class, int wait)
{
	switch (class) {
	case MC_MBUF:
		if (wait & MCR_COMP)
			return (!mcache_bkt_isempty(m_cache(MC_MBUF_CL)) ||
			    !mcache_bkt_isempty(m_cache(MC_MBUF_BIGCL)));
		break;

	case MC_CL:
		if (wait & MCR_COMP)
			return (!mcache_bkt_isempty(m_cache(MC_MBUF_CL)));
		break;

	case MC_BIGCL:
		if (wait & MCR_COMP)
			return (!mcache_bkt_isempty(m_cache(MC_MBUF_BIGCL)));
		break;

	case MC_16KCL:
		if (wait & MCR_COMP)
			return (!mcache_bkt_isempty(m_cache(MC_MBUF_16KCL)));
		break;

	case MC_MBUF_CL:
	case MC_MBUF_BIGCL:
	case MC_MBUF_16KCL:
		break;

	default:
		VERIFY(0);
		/* NOTREACHED */
	}

	return (!mcache_bkt_isempty(m_cache(class)));
}