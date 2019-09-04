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
typedef  scalar_t__ uint32_t ;
struct mbuf {int dummy; } ;
struct ifnet_stat_increment_param {int packets_in; scalar_t__ bytes_in; } ;
typedef  int /*<<< orphan*/  ifnet_t ;

/* Variables and functions */
 scalar_t__ ETHER_HDR_LEN ; 
 int /*<<< orphan*/  ifnet_input (int /*<<< orphan*/ ,struct mbuf*,struct ifnet_stat_increment_param*) ; 
 scalar_t__ mbuf_pkthdr_len (struct mbuf*) ; 

__attribute__((used)) static void
feth_enqueue_input(ifnet_t ifp, struct mbuf * m)
{
	struct ifnet_stat_increment_param stats = {};

	stats.packets_in = 1;
	stats.bytes_in = (uint32_t)mbuf_pkthdr_len(m) + ETHER_HDR_LEN;
	ifnet_input(ifp, m, &stats);
}