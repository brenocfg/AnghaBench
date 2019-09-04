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

/* Variables and functions */
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  tcp_out_cksum_stats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udp_out_cksum_stats (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ip_out_cksum_stats(int proto, u_int32_t len)
{
	switch (proto) {
	case IPPROTO_TCP:
		tcp_out_cksum_stats(len);
		break;
	case IPPROTO_UDP:
		udp_out_cksum_stats(len);
		break;
	default:
		/* keep only TCP or UDP stats for now */
		break;
	}
}