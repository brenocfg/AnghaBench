#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  posix_spawn_file_actions_t ;
typedef  TYPE_1__* _posix_spawn_file_actions_t ;
struct TYPE_2__ {scalar_t__ psfa_act_count; int /*<<< orphan*/  psfa_act_alloc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PSF_ACTIONS_INIT_COUNT ; 
 int /*<<< orphan*/  PSF_ACTIONS_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 

int
posix_spawn_file_actions_init(posix_spawn_file_actions_t *file_actions)
{
	_posix_spawn_file_actions_t *psactsp = (_posix_spawn_file_actions_t *)file_actions;
	int	err = 0;

	if ((*psactsp = (_posix_spawn_file_actions_t)malloc(PSF_ACTIONS_SIZE(PSF_ACTIONS_INIT_COUNT))) == NULL) {
		err = ENOMEM;
	} else {
		(*psactsp)->psfa_act_alloc = PSF_ACTIONS_INIT_COUNT;
		(*psactsp)->psfa_act_count = 0;
	}

	return (err);
}