#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ki_tid; int /*<<< orphan*/  ki_pid; int /*<<< orphan*/  ki_tdev; } ;
struct TYPE_7__ {TYPE_1__* ki_p; } ;
struct TYPE_6__ {scalar_t__ ki_tdev; } ;
typedef  TYPE_2__ KINFO ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_RETURN (TYPE_2__ const*,TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 scalar_t__ NODEV ; 
 scalar_t__ SORTCPU ; 
 scalar_t__ SORTMEM ; 
 int /*<<< orphan*/  ki_memsize ; 
 TYPE_3__* ki_p ; 
 int /*<<< orphan*/  ki_pcpu ; 
 scalar_t__ sortby ; 

__attribute__((used)) static int
pscomp(const void *a, const void *b)
{
	const KINFO *ka, *kb;

	ka = a;
	kb = b;
	/* SORTCPU and SORTMEM are sorted in descending order. */
	if (sortby == SORTCPU)
		DIFF_RETURN(kb, ka, ki_pcpu);
	if (sortby == SORTMEM)
		DIFF_RETURN(kb, ka, ki_memsize);
	/*
	 * TTY's are sorted in ascending order, except that all NODEV
	 * processes come before all processes with a device.
	 */
	if (ka->ki_p->ki_tdev != kb->ki_p->ki_tdev) {
		if (ka->ki_p->ki_tdev == NODEV)
			return (-1);
		if (kb->ki_p->ki_tdev == NODEV)
			return (1);
		DIFF_RETURN(ka, kb, ki_p->ki_tdev);
	}

	/* PID's and TID's (threads) are sorted in ascending order. */
	DIFF_RETURN(ka, kb, ki_p->ki_pid);
	DIFF_RETURN(ka, kb, ki_p->ki_tid);
	return (0);
}