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
struct TYPE_2__ {struct sackhole* nexthole; } ;
struct tcpcb {int /*<<< orphan*/  snd_holes; TYPE_1__ sackhint; } ;
struct sackhole {int dummy; } ;

/* Variables and functions */
 struct sackhole* TAILQ_NEXT (struct sackhole*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct sackhole*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scblink ; 
 int /*<<< orphan*/  tcp_sackhole_free (struct tcpcb*,struct sackhole*) ; 

__attribute__((used)) static void
tcp_sackhole_remove(struct tcpcb *tp, struct sackhole *hole)
{
	/* Update SACK hint. */
	if (tp->sackhint.nexthole == hole)
		tp->sackhint.nexthole = TAILQ_NEXT(hole, scblink);

	/* Remove this SACK hole. */
	TAILQ_REMOVE(&tp->snd_holes, hole, scblink);

	/* Free this SACK hole. */
	tcp_sackhole_free(tp, hole);
}