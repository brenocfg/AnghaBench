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
struct tcpcb {int /*<<< orphan*/  snd_numholes; } ;
struct sackhole {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSDecrementAtomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sack_hole_zone ; 
 int /*<<< orphan*/  tcp_sack_globalholes ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct sackhole*) ; 

__attribute__((used)) static void
tcp_sackhole_free(struct tcpcb *tp, struct sackhole *hole)
{
	zfree(sack_hole_zone, hole);

	tp->snd_numholes--;
	OSDecrementAtomic(&tcp_sack_globalholes);
}