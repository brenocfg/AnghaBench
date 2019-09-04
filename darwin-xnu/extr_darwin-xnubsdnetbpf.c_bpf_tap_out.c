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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  ifnet_t ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_tap_mbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int) ; 

void
bpf_tap_out(
	ifnet_t		ifp,
	u_int32_t	dlt,
	mbuf_t		m,
	void*		hdr,
	size_t		hlen)
{
	bpf_tap_mbuf(ifp, dlt, m, hdr, hlen, 1);
}