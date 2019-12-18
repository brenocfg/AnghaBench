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
struct tcpcb {int /*<<< orphan*/ * sackblks; scalar_t__ rcv_numsacks; } ;
struct sackblk {int dummy; } ;

/* Variables and functions */
 int MAX_SACK_BLKS ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

void
tcp_clean_sackreport( struct tcpcb *tp)
{

	tp->rcv_numsacks = 0;
	bzero(&tp->sackblks[0], sizeof (struct sackblk) * MAX_SACK_BLKS);
}