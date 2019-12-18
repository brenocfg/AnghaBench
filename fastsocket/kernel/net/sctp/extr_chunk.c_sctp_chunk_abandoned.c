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
struct sctp_datamsg {int /*<<< orphan*/  expires_at; int /*<<< orphan*/  can_abandon; } ;
struct sctp_chunk {struct sctp_datamsg* msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sctp_chunk_abandoned(struct sctp_chunk *chunk)
{
	struct sctp_datamsg *msg = chunk->msg;

	if (!msg->can_abandon)
		return 0;

	if (time_after(jiffies, msg->expires_at))
		return 1;

	return 0;
}