#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* buf_t ;
struct TYPE_4__ {size_t b_whichq; int /*<<< orphan*/  b_timestamp; } ;

/* Variables and functions */
 size_t BQ_LAUNDRY ; 
 int /*<<< orphan*/  binstailfree (TYPE_1__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  blaundrycnt ; 
 int /*<<< orphan*/  buf_timestamp () ; 
 int /*<<< orphan*/ * bufqueues ; 

__attribute__((used)) static __inline__ void
bmovelaundry(buf_t bp)
{
	bp->b_whichq = BQ_LAUNDRY;
	bp->b_timestamp = buf_timestamp();
	binstailfree(bp, &bufqueues[BQ_LAUNDRY], BQ_LAUNDRY);
	blaundrycnt++;
}