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
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  m_ext_paired_activate (int /*<<< orphan*/ ) ; 
 scalar_t__ mbuf_ring_cluster_is_active (int /*<<< orphan*/ ) ; 

errno_t
mbuf_ring_cluster_activate(mbuf_t mbuf)
{
	if (mbuf_ring_cluster_is_active(mbuf))
		return (EBUSY);

	m_ext_paired_activate(mbuf);
	return (0);
}