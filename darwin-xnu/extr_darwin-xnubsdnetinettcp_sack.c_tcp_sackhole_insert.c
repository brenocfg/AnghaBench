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
typedef  int /*<<< orphan*/  tcp_seq ;
struct TYPE_2__ {struct sackhole* nexthole; } ;
struct tcpcb {TYPE_1__ sackhint; int /*<<< orphan*/  snd_holes; } ;
struct sackhole {int /*<<< orphan*/  rxmit_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (int /*<<< orphan*/ *,struct sackhole*,struct sackhole*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct sackhole*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scblink ; 
 int /*<<< orphan*/  tcp_now ; 
 struct sackhole* tcp_sackhole_alloc (struct tcpcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sackhole *
tcp_sackhole_insert(struct tcpcb *tp, tcp_seq start, tcp_seq end,
		    struct sackhole *after)
{
	struct sackhole *hole;

	/* Allocate a new SACK hole. */
	hole = tcp_sackhole_alloc(tp, start, end);
	if (hole == NULL)
		return NULL;
	hole->rxmit_start = tcp_now;
	/* Insert the new SACK hole into scoreboard */
	if (after != NULL)
		TAILQ_INSERT_AFTER(&tp->snd_holes, after, hole, scblink);
	else
		TAILQ_INSERT_TAIL(&tp->snd_holes, hole, scblink);

	/* Update SACK hint. */
	if (tp->sackhint.nexthole == NULL)
		tp->sackhint.nexthole = hole;

	return(hole);
}