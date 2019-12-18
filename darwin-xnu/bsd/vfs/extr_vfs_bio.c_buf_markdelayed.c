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
struct TYPE_4__ {int /*<<< orphan*/  b_flags; int /*<<< orphan*/  b_vp; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_DELWRI ; 
 int /*<<< orphan*/  B_DONE ; 
 int /*<<< orphan*/  ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAddAtomicLong (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_reassign (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nbdwrite ; 

void
buf_markdelayed(buf_t bp) {
  
	if (!ISSET(bp->b_flags, B_DELWRI)) {
		SET(bp->b_flags, B_DELWRI);

		OSAddAtomicLong(1, &nbdwrite);
		buf_reassign(bp, bp->b_vp);
	}
        SET(bp->b_flags, B_DONE);
}