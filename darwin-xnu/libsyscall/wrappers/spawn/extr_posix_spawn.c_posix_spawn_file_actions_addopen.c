#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * posix_spawn_file_actions_t ;
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_5__ {int psfao_oflag; int /*<<< orphan*/  psfao_path; int /*<<< orphan*/  psfao_mode; } ;
struct TYPE_6__ {int psfaa_filedes; TYPE_1__ psfaa_openargs; int /*<<< orphan*/  psfaa_type; } ;
typedef  TYPE_2__ _psfa_action_t ;
typedef  TYPE_3__* _posix_spawn_file_actions_t ;
struct TYPE_7__ {scalar_t__ psfa_act_count; scalar_t__ psfa_act_alloc; TYPE_2__* psfa_act_acts; } ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int ENOMEM ; 
 int OPEN_MAX ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  PSFA_OPEN ; 
 scalar_t__ _posix_spawn_file_actions_grow (TYPE_3__**) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int
posix_spawn_file_actions_addopen(
		posix_spawn_file_actions_t * __restrict file_actions,
		int filedes, const char * __restrict path, int oflag,
		mode_t mode)
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

	psfileact->psfaa_type = PSFA_OPEN;
	psfileact->psfaa_filedes = filedes;
	psfileact->psfaa_openargs.psfao_oflag = oflag;
	psfileact->psfaa_openargs.psfao_mode = mode;
	strlcpy(psfileact->psfaa_openargs.psfao_path, path, PATH_MAX);

	return (0);
}