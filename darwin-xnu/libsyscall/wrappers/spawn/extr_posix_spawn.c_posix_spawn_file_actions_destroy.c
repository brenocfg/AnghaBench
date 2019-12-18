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
typedef  int /*<<< orphan*/  _posix_spawn_file_actions_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

int
posix_spawn_file_actions_destroy(posix_spawn_file_actions_t *file_actions)
{
	_posix_spawn_file_actions_t psacts;

	if (file_actions == NULL || *file_actions == NULL)
		return EINVAL;

	psacts = *(_posix_spawn_file_actions_t *)file_actions;
	free(psacts);
	*file_actions = NULL;

	return (0);
}