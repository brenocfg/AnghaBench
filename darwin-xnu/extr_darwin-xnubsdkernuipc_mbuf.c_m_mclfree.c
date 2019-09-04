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
 int /*<<< orphan*/  MC_CL ; 
 int /*<<< orphan*/  m_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
m_mclfree(caddr_t p)
{
	mcache_free(m_cache(MC_CL), p);
}