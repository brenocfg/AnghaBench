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
struct _posix_spawn_persona_info {int dummy; } ;
typedef  int /*<<< orphan*/ * posix_spawnattr_t ;
typedef  TYPE_1__* _posix_spawnattr_t ;
struct TYPE_2__ {struct _posix_spawn_persona_info* psa_persona_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  free (struct _posix_spawn_persona_info*) ; 

__attribute__((used)) static int
posix_spawn_destroypersona_info_np(posix_spawnattr_t *attr)
{
	_posix_spawnattr_t psattr;
	struct _posix_spawn_persona_info *persona;

	if (attr == NULL || *attr == NULL)
		return EINVAL;

	psattr = *(_posix_spawnattr_t *)attr;
	persona = psattr->psa_persona_info;
	if (persona == NULL)
		return EINVAL;

	psattr->psa_persona_info = NULL;
	free(persona);
	return 0;
}