#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * posix_spawn_file_actions_t ;
typedef  int /*<<< orphan*/  _psfa_action_t ;
typedef  int /*<<< orphan*/  _posix_spawn_file_actions_t ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int OPEN_MAX ; 

int
posix_spawn_file_actions_addinherit_np(posix_spawn_file_actions_t *file_actions,
		int filedes)
{
	_posix_spawn_file_actions_t *psactsp;
	_psfa_action_t *psfileact;

	if (file_actions == NULL || *file_actions == NULL)
		return (EINVAL);

	psactsp = (_posix_spawn_file_actions_t *)file_actions;
	/* Range check; required by POSIX */
	if (filedes < 0 || filedes >= OPEN_MAX)
		return (EBADF);

#if defined(POSIX_SPAWN_CLOEXEC_DEFAULT)	// TODO: delete this check
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

	psfileact->psfaa_type = PSFA_INHERIT;
	psfileact->psfaa_filedes = filedes;
#endif
	return (0);
}