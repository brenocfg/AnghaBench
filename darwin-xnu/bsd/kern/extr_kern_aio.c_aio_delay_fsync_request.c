#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {TYPE_1__* procp; } ;
typedef  TYPE_2__ aio_workq_entry ;
struct TYPE_5__ {int /*<<< orphan*/  p_aio_activeq; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_2__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static boolean_t
aio_delay_fsync_request( aio_workq_entry *entryp )
{
	if (entryp == TAILQ_FIRST(&entryp->procp->p_aio_activeq)) {
		return FALSE;
	}
		
	return TRUE;
}