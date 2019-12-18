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
typedef  int /*<<< orphan*/ * posix_spawn_file_actions_t ;
struct TYPE_4__ {int psfaa_filedes; int /*<<< orphan*/  psfaa_type; } ;
typedef  TYPE_1__ _psfa_action_t ;
typedef  TYPE_2__* _posix_spawn_file_actions_t ;
struct TYPE_5__ {scalar_t__ psfa_act_count; scalar_t__ psfa_act_alloc; TYPE_1__* psfa_act_acts; } ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int ENOMEM ; 
 int OPEN_MAX ; 
 int /*<<< orphan*/  PSFA_CLOSE ; 
 scalar_t__ _posix_spawn_file_actions_grow (TYPE_2__**) ; 

int
posix_spawn_file_actions_addclose(posix_spawn_file_actions_t *file_actions,
		int filedes)
{
	_posix_spawn_file_actions_t *psactsp;
	_psfa_action_t *psfileact;

	if (file_actions == NULL || *file_actions == NULL)
		return EINVAL;

	psactsp = (_posix_spawn_file_actions_t *)file_actions;
	/* Range check; required by POSIX */
	if (filedes < 0 || filedes >= OPEN_MAX)
		return (EBADF);

	/* If we do not have enough slots, grow the structure */
	if ((*psactsp)->psfa_act_count == (*psactsp)->psfa_act_alloc) {
		/* need to grow file actions structure */
		if (_posix_spawn_file_actions_grow(psactsp))
			return (ENOMEM);
	}

	/*
	 * Allocate next available slot and fill it out
	 */
	psfileact = &(*psactsp)->psfa_act_acts[(*psactsp)->psfa_act_count++];

	psfileact->psfaa_type = PSFA_CLOSE;
	psfileact->psfaa_filedes = filedes;

	return (0);
}