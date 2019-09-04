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

/* Variables and functions */
 int m_ext_paired_is_active (int /*<<< orphan*/ ) ; 

int
mbuf_ring_cluster_is_active(mbuf_t mbuf)
{
	return (m_ext_paired_is_active(mbuf));
}