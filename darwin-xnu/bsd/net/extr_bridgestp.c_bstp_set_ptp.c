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
struct bstp_state {int dummy; } ;
struct bstp_port {int bp_ptp_link; struct bstp_state* bp_bs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTP_LOCK (struct bstp_state*) ; 
 int /*<<< orphan*/  BSTP_UNLOCK (struct bstp_state*) ; 

int
bstp_set_ptp(struct bstp_port *bp, int set)
{
	struct bstp_state *bs = bp->bp_bs;

	BSTP_LOCK(bs);
	bp->bp_ptp_link = set;
	BSTP_UNLOCK(bs);
	return (0);
}