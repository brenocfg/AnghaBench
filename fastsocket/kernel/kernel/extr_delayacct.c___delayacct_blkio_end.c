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
struct TYPE_4__ {TYPE_1__* delays; } ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  blkio_count; int /*<<< orphan*/  blkio_delay; int /*<<< orphan*/  blkio_end; int /*<<< orphan*/  blkio_start; int /*<<< orphan*/  swapin_count; int /*<<< orphan*/  swapin_delay; } ;

/* Variables and functions */
 int DELAYACCT_PF_SWAPIN ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  delayacct_end (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void __delayacct_blkio_end(void)
{
	if (current->delays->flags & DELAYACCT_PF_SWAPIN)
		/* Swapin block I/O */
		delayacct_end(&current->delays->blkio_start,
			&current->delays->blkio_end,
			&current->delays->swapin_delay,
			&current->delays->swapin_count);
	else	/* Other block I/O */
		delayacct_end(&current->delays->blkio_start,
			&current->delays->blkio_end,
			&current->delays->blkio_delay,
			&current->delays->blkio_count);
}