#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct magic_set* li; } ;
struct TYPE_3__ {struct magic_set* buf; struct magic_set* pbuf; } ;
struct magic_set {TYPE_2__ c; TYPE_1__ o; int /*<<< orphan*/ * mlist; } ;

/* Variables and functions */
 size_t MAGIC_SETS ; 
 int /*<<< orphan*/  free (struct magic_set*) ; 
 int /*<<< orphan*/  mlist_free (int /*<<< orphan*/ ) ; 

void
file_ms_free(struct magic_set *ms)
{
	size_t i;
	if (ms == NULL)
		return;
	for (i = 0; i < MAGIC_SETS; i++)
		mlist_free(ms->mlist[i]);
	free(ms->o.pbuf);
	free(ms->o.buf);
	free(ms->c.li);
	free(ms);
}