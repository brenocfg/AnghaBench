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
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int MCR_NOSLEEP ; 
 int MCR_TRYHARD ; 
 int /*<<< orphan*/  MC_CL ; 
 int MSLEEPF (int) ; 
 int /*<<< orphan*/  m_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcache_alloc (int /*<<< orphan*/ ,int) ; 

caddr_t
m_mclalloc(int wait)
{
	int mcflags = MSLEEPF(wait);

	/* Is this due to a non-blocking retry?  If so, then try harder */
	if (mcflags & MCR_NOSLEEP)
		mcflags |= MCR_TRYHARD;

	return (mcache_alloc(m_cache(MC_CL), mcflags));
}