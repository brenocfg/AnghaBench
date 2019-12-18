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
struct sctp_bind_addr {int /*<<< orphan*/  port; int /*<<< orphan*/  address_list; scalar_t__ malloced; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

void sctp_bind_addr_init(struct sctp_bind_addr *bp, __u16 port)
{
	bp->malloced = 0;

	INIT_LIST_HEAD(&bp->address_list);
	bp->port = port;
}