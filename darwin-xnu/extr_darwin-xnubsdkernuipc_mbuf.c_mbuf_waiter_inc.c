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
typedef  scalar_t__ mbuf_class_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ MC_16KCL ; 
 scalar_t__ MC_BIGCL ; 
 scalar_t__ MC_CL ; 
 scalar_t__ MC_MBUF_16KCL ; 
 scalar_t__ MC_MBUF_BIGCL ; 
 scalar_t__ MC_MBUF_CL ; 
 int /*<<< orphan*/  m_cache (scalar_t__) ; 
 int /*<<< orphan*/  mcache_waiter_inc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mbuf_waiter_inc(mbuf_class_t class, boolean_t comp)
{
	mcache_waiter_inc(m_cache(class));
	if (comp) {
		if (class == MC_CL) {
			mcache_waiter_inc(m_cache(MC_MBUF_CL));
		} else if (class == MC_BIGCL) {
			mcache_waiter_inc(m_cache(MC_MBUF_BIGCL));
		} else if (class == MC_16KCL) {
			mcache_waiter_inc(m_cache(MC_MBUF_16KCL));
		} else {
			mcache_waiter_inc(m_cache(MC_MBUF_CL));
			mcache_waiter_inc(m_cache(MC_MBUF_BIGCL));
		}
	}
}