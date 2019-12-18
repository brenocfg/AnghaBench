#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct _reent {int /*<<< orphan*/  _errno; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {scalar_t__ dirStruct; } ;
struct TYPE_5__ {TYPE_4__* partition; int /*<<< orphan*/  startCluster; int /*<<< orphan*/  currentEntry; int /*<<< orphan*/  validEntry; int /*<<< orphan*/  inUse; } ;
typedef  TYPE_1__ DIR_STATE_STRUCT ;
typedef  TYPE_2__ DIR_ITER ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  _FAT_directory_getFirstEntry (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FAT_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _FAT_unlock (int /*<<< orphan*/ *) ; 

int _FAT_dirreset_r (struct _reent *r, DIR_ITER *dirState)
{
	DIR_STATE_STRUCT* state = (DIR_STATE_STRUCT*) (dirState->dirStruct);

	_FAT_lock(&state->partition->lock);

	/* Make sure we are still using this entry */
	if (!state->inUse)
   {
		_FAT_unlock(&state->partition->lock);
		r->_errno = EBADF;
		return -1;
	}

	/* Get the first entry for use with a call to dirnext */
	state->validEntry =
		_FAT_directory_getFirstEntry (state->partition, &(state->currentEntry), state->startCluster);

	_FAT_unlock(&state->partition->lock);
	return 0;
}