#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint64_t ;
struct TYPE_6__ {unsigned int dofh_loadsz; } ;
typedef  TYPE_1__ dof_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  PEReadNVRAMProperty (char const*,TYPE_1__*,unsigned int*) ; 
 int /*<<< orphan*/  dtrace_are_restrictions_relaxed () ; 
 int /*<<< orphan*/  dtrace_dof_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  dtrace_dof_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ dtrace_dof_maxsize ; 
 scalar_t__ dtrace_is_restricted () ; 
 TYPE_1__* kmem_alloc_aligned (unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dof_hdr_t *
dtrace_dof_property(const char *name)
{
	unsigned int len = 0;
	dof_hdr_t *dof;

	if (dtrace_is_restricted() && !dtrace_are_restrictions_relaxed()) {
		return NULL;
	}

	if (!PEReadNVRAMProperty(name, NULL, &len)) {
		return NULL;
	}

	dof = kmem_alloc_aligned(len, 8, KM_SLEEP);

	if (!PEReadNVRAMProperty(name, dof, &len)) {
		dtrace_dof_destroy(dof);
		dtrace_dof_error(NULL, "unreadable DOF");
		return NULL;
	}

	if (len < sizeof (dof_hdr_t)) {
		dtrace_dof_destroy(dof);
		dtrace_dof_error(NULL, "truncated header");
		return (NULL);
	}

	if (len < dof->dofh_loadsz) {
		dtrace_dof_destroy(dof);
		dtrace_dof_error(NULL, "truncated DOF");
		return (NULL);
	}

	if (len != dof->dofh_loadsz) {
		dtrace_dof_destroy(dof);
		dtrace_dof_error(NULL, "invalid DOF size");
		return (NULL);
	}

	if (dof->dofh_loadsz >= (uint64_t)dtrace_dof_maxsize) {
		dtrace_dof_destroy(dof);
		dtrace_dof_error(NULL, "oversized DOF");
		return (NULL);
	}

	return (dof);
}