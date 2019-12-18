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
struct pshmobj {int pshm_flags; struct pshmobj* pshmo_next; int /*<<< orphan*/  pshmo_memobject; struct pshmobj* pshm_memobjects; int /*<<< orphan*/  pshm_usecount; } ;
struct pshminfo {int pshm_flags; struct pshminfo* pshmo_next; int /*<<< orphan*/  pshmo_memobject; struct pshminfo* pshm_memobjects; int /*<<< orphan*/  pshm_usecount; } ;
struct pshmcache {int pshm_flags; struct pshmcache* pshmo_next; int /*<<< orphan*/  pshmo_memobject; struct pshmcache* pshm_memobjects; int /*<<< orphan*/  pshm_usecount; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FREE (struct pshmobj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_SHM ; 
 int PSHM_ALLOCATED ; 
 int PSHM_DEFINED ; 
 int PSHM_INDELETE ; 
 int PSHM_REMOVED ; 
 int /*<<< orphan*/  PSHM_SUBSYS_ASSERT_HELD () ; 
 int /*<<< orphan*/  mac_posixshm_label_destroy (struct pshmobj*) ; 
 int /*<<< orphan*/  mach_memory_entry_port_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pshm_cache_delete (struct pshmobj*) ; 

__attribute__((used)) static int
pshm_unlink_internal(struct pshminfo *pinfo, struct pshmcache *pcache)
{
	struct pshmobj *pshmobj, *pshmobj_next;

	PSHM_SUBSYS_ASSERT_HELD();

	if (!pinfo || !pcache)
		return EINVAL;

	if ((pinfo->pshm_flags & (PSHM_DEFINED | PSHM_ALLOCATED)) == 0)
		return EINVAL;

	if (pinfo->pshm_flags & PSHM_INDELETE)
		return 0;

	pinfo->pshm_flags |= PSHM_INDELETE;
	pinfo->pshm_usecount--;

	pshm_cache_delete(pcache);
	pinfo->pshm_flags |= PSHM_REMOVED;

	/* release the existence reference */
	if (!pinfo->pshm_usecount) {
#if CONFIG_MACF
		mac_posixshm_label_destroy(pinfo);
#endif
		/*
		 * If this is the last reference going away on the object,
		 * then we need to destroy the backing object.  The name
		 * has an implied but uncounted reference on the object,
		 * once it's created, since it's used as a rendezvous, and
		 * therefore may be subsequently reopened.
		 */
		for (pshmobj = pinfo->pshm_memobjects;
		     pshmobj != NULL;
		     pshmobj = pshmobj_next) {
			mach_memory_entry_port_release(pshmobj->pshmo_memobject);
			pshmobj_next = pshmobj->pshmo_next;
			FREE(pshmobj, M_SHM);
		}
		FREE(pinfo,M_SHM);
	}

	FREE(pcache, M_SHM);

	return 0;
}