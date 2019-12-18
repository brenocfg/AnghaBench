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
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC_CL ; 
 int /*<<< orphan*/  M_WAIT ; 
 struct mbuf* m_getpackets_internal (unsigned int*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_maxsize (int /*<<< orphan*/ ) ; 

struct mbuf *
m_getpacket(void)
{
	unsigned int num_needed = 1;

	return (m_getpackets_internal(&num_needed, 1, M_WAIT, 1,
	    m_maxsize(MC_CL)));
}