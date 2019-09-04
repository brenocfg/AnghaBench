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
struct bstp_state {int bs_bridge_priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTP_LOCK (struct bstp_state*) ; 
 int BSTP_MAX_PRIORITY ; 
 int /*<<< orphan*/  BSTP_UNLOCK (struct bstp_state*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  bstp_reinit (struct bstp_state*) ; 

int
bstp_set_priority(struct bstp_state *bs, int pri)
{
	if (pri < 0 || pri > BSTP_MAX_PRIORITY)
		return (EINVAL);

	/* Limit to steps of 4096 */
	pri -= pri % 4096;

	BSTP_LOCK(bs);
	bs->bs_bridge_priority = pri;
	bstp_reinit(bs);
	BSTP_UNLOCK(bs);
	return (0);
}