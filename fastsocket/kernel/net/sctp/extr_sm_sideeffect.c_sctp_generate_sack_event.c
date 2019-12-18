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
struct sctp_association {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_EVENT_TIMEOUT_SACK ; 
 int /*<<< orphan*/  sctp_generate_timeout_event (struct sctp_association*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sctp_generate_sack_event(unsigned long data)
{
	struct sctp_association *asoc = (struct sctp_association *) data;
	sctp_generate_timeout_event(asoc, SCTP_EVENT_TIMEOUT_SACK);
}