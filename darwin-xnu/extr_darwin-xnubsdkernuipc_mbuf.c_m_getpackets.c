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
 struct mbuf* m_getpackets_internal (unsigned int*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_maxsize (int /*<<< orphan*/ ) ; 

struct mbuf *
m_getpackets(int num_needed, int num_with_pkthdrs, int how)
{
	unsigned int n = num_needed;

	return (m_getpackets_internal(&n, num_with_pkthdrs, how, 0,
	    m_maxsize(MC_CL)));
}