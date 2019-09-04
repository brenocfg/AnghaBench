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
struct timespec {int tv_sec; scalar_t__ tv_nsec; } ;
struct bstp_state {int bs_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTP_LOCK (struct bstp_state*) ; 
 int /*<<< orphan*/  BSTP_UNLOCK (struct bstp_state*) ; 
 int /*<<< orphan*/  bsd_timeout (int /*<<< orphan*/ ,struct bstp_state*,struct timespec*) ; 
 int /*<<< orphan*/  bstp_reinit (struct bstp_state*) ; 
 int /*<<< orphan*/  bstp_tick ; 

void
bstp_init(struct bstp_state *bs)
{
	struct timespec ts;

	ts.tv_sec = 1;
	ts.tv_nsec = 0;

	BSTP_LOCK(bs);
	bsd_timeout(bstp_tick, bs, &ts);
	bs->bs_running = 1;
	bstp_reinit(bs);
	BSTP_UNLOCK(bs);
}