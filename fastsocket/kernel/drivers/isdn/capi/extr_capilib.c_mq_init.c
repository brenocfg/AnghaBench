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
typedef  size_t u_int ;
struct capilib_ncci {size_t winsize; TYPE_1__* msgidpool; TYPE_1__* msgidfree; scalar_t__ nmsg; int /*<<< orphan*/ * msgidlast; int /*<<< orphan*/ * msgidqueue; } ;
struct TYPE_2__ {struct TYPE_2__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void mq_init(struct capilib_ncci * np)
{
	u_int i;
	np->msgidqueue = NULL;
	np->msgidlast = NULL;
	np->nmsg = 0;
	memset(np->msgidpool, 0, sizeof(np->msgidpool));
	np->msgidfree = &np->msgidpool[0];
	for (i = 1; i < np->winsize; i++) {
		np->msgidpool[i].next = np->msgidfree;
		np->msgidfree = &np->msgidpool[i];
	}
}