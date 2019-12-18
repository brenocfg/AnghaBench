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
struct sctp_bind_addr {scalar_t__ malloced; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_DBG_OBJCNT_DEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bind_addr ; 
 int /*<<< orphan*/  kfree (struct sctp_bind_addr*) ; 
 int /*<<< orphan*/  sctp_bind_addr_clean (struct sctp_bind_addr*) ; 

void sctp_bind_addr_free(struct sctp_bind_addr *bp)
{
	/* Empty the bind address list. */
	sctp_bind_addr_clean(bp);

	if (bp->malloced) {
		kfree(bp);
		SCTP_DBG_OBJCNT_DEC(bind_addr);
	}
}