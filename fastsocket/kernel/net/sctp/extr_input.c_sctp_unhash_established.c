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
struct sctp_association {scalar_t__ temp; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sctp_unhash_established (struct sctp_association*) ; 
 int /*<<< orphan*/  sctp_local_bh_disable () ; 
 int /*<<< orphan*/  sctp_local_bh_enable () ; 

void sctp_unhash_established(struct sctp_association *asoc)
{
	if (asoc->temp)
		return;

	sctp_local_bh_disable();
	__sctp_unhash_established(asoc);
	sctp_local_bh_enable();
}