#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* buf_t ;
struct TYPE_4__ {int /*<<< orphan*/  le_next; } ;
struct TYPE_5__ {int /*<<< orphan*/  b_flags; TYPE_1__ b_vnbufs; void* b_wcred; void* b_rcred; int /*<<< orphan*/  b_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_INVAL ; 
 void* NOCRED ; 
 int /*<<< orphan*/  NODEV ; 
 int /*<<< orphan*/  NOLIST ; 
 int /*<<< orphan*/  bzero (char*,int) ; 

__attribute__((used)) static __inline__ void
bufhdrinit(buf_t bp)
{
	bzero((char *)bp, sizeof *bp);
	bp->b_dev = NODEV;
	bp->b_rcred = NOCRED;
	bp->b_wcred = NOCRED;
	bp->b_vnbufs.le_next = NOLIST;
	bp->b_flags = B_INVAL;

	return;
}