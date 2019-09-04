#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct _posix_spawn_coalition_info {TYPE_1__* psci_info; } ;
typedef  int /*<<< orphan*/ * posix_spawnattr_t ;
typedef  TYPE_2__* _posix_spawnattr_t ;
struct TYPE_4__ {struct _posix_spawn_coalition_info* psa_coalition_info; } ;
struct TYPE_3__ {int psci_role; int /*<<< orphan*/  psci_id; } ;

/* Variables and functions */
 int COALITION_TYPE_MAX ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (struct _posix_spawn_coalition_info*,int /*<<< orphan*/ ,int) ; 

int posix_spawnattr_setcoalition_np(const posix_spawnattr_t * __restrict attr,
				    uint64_t coalitionid, int type, int role)
{
	_posix_spawnattr_t psattr;
	struct _posix_spawn_coalition_info *coal_info;

	if (attr == NULL || *attr == NULL) {
		return EINVAL;
	}
	if (type < 0 || type > COALITION_TYPE_MAX)
		return EINVAL;

	psattr = *(_posix_spawnattr_t *)attr;

	coal_info = psattr->psa_coalition_info;
	if (!coal_info) {
		coal_info = (struct _posix_spawn_coalition_info *)malloc(sizeof(*coal_info));
		if (!coal_info)
			return ENOMEM;
		memset(coal_info, 0, sizeof(*coal_info));
		psattr->psa_coalition_info = coal_info;
	}

	coal_info->psci_info[type].psci_id   = coalitionid;
	coal_info->psci_info[type].psci_role = role;

	return 0;
}