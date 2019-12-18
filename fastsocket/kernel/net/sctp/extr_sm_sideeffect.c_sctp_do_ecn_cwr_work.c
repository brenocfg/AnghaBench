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
struct sctp_association {scalar_t__ need_ecne; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */

__attribute__((used)) static void sctp_do_ecn_cwr_work(struct sctp_association *asoc,
				 __u32 lowest_tsn)
{
	/* Turn off ECNE getting auto-prepended to every outgoing
	 * packet
	 */
	asoc->need_ecne = 0;
}