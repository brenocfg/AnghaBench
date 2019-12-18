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
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  m_do_tx_compl_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

errno_t
ifnet_tx_compl(ifnet_t ifp, mbuf_t m)
{
	m_do_tx_compl_callback(m, ifp);

	return (0);
}