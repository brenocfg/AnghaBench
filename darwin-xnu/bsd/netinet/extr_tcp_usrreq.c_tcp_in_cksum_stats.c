#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  tcps_rcv_swcsum_bytes; int /*<<< orphan*/  tcps_rcv_swcsum; } ;

/* Variables and functions */
 TYPE_1__ tcpstat ; 

void
tcp_in_cksum_stats(u_int32_t len)
{
	tcpstat.tcps_rcv_swcsum++;
	tcpstat.tcps_rcv_swcsum_bytes += len;
}