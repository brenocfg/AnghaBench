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
typedef  scalar_t__ uint32_t ;
struct llinfo_arp {int /*<<< orphan*/  la_holdq; } ;

/* Variables and functions */
 int M_WAITOK ; 
 int /*<<< orphan*/  QP_MBUF ; 
 int /*<<< orphan*/  Q_DROPHEAD ; 
 int /*<<< orphan*/  _qinit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ arp_maxhold ; 
 int /*<<< orphan*/  bzero (struct llinfo_arp*,int) ; 
 int /*<<< orphan*/  llinfo_arp_zone ; 
 struct llinfo_arp* zalloc (int /*<<< orphan*/ ) ; 
 struct llinfo_arp* zalloc_noblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct llinfo_arp *
arp_llinfo_alloc(int how)
{
	struct llinfo_arp *la;

	la = (how == M_WAITOK) ? zalloc(llinfo_arp_zone) :
	    zalloc_noblock(llinfo_arp_zone);
	if (la != NULL) {
		bzero(la, sizeof (*la));
		/*
		 * The type of queue (Q_DROPHEAD) here is just a hint;
		 * the actual logic that works on this queue performs
		 * a head drop, details in arp_llinfo_addq().
		 */
		_qinit(&la->la_holdq, Q_DROPHEAD, (arp_maxhold == 0) ?
		    (uint32_t)-1 : arp_maxhold, QP_MBUF);
	}

	return (la);
}