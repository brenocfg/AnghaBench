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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uid_t ;
struct _posix_spawn_persona_info {int pspi_flags; int /*<<< orphan*/  pspi_id; scalar_t__* pspi_groups; scalar_t__ pspi_ngroups; scalar_t__ pspi_gid; scalar_t__ pspi_uid; } ;
typedef  int /*<<< orphan*/ * posix_spawnattr_t ;
typedef  TYPE_1__* _posix_spawnattr_t ;
struct TYPE_2__ {struct _posix_spawn_persona_info* psa_persona_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int POSIX_SPAWN_PERSONA_ALL_FLAGS ; 
 scalar_t__ malloc (int) ; 

int
posix_spawnattr_set_persona_np(const posix_spawnattr_t * __restrict attr, uid_t persona_id, uint32_t flags)
{
	_posix_spawnattr_t psattr;
	struct _posix_spawn_persona_info *persona;

	if (attr == NULL || *attr == NULL)
		return EINVAL;

	if (flags & ~POSIX_SPAWN_PERSONA_ALL_FLAGS)
		return EINVAL;

	psattr = *(_posix_spawnattr_t *)attr;

	persona = psattr->psa_persona_info;
	if (!persona) {
		persona = (struct _posix_spawn_persona_info *)malloc(sizeof(*persona));
		if (!persona)
			return ENOMEM;
		persona->pspi_uid = 0;
		persona->pspi_gid = 0;
		persona->pspi_ngroups = 0;
		persona->pspi_groups[0] = 0;

		psattr->psa_persona_info = persona;
	}

	persona->pspi_id = persona_id;
	persona->pspi_flags = flags;

	return 0;
}