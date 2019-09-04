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
struct vfs_drt_clustermap {int /*<<< orphan*/  scm_lastclean; int /*<<< orphan*/  scm_iskips; int /*<<< orphan*/  scm_buckets; int /*<<< orphan*/  scm_modulus; } ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRT_DEBUG_SCMDATA ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  vfs_drt_free_map (struct vfs_drt_clustermap*) ; 
 int /*<<< orphan*/  vfs_drt_trace (struct vfs_drt_clustermap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
vfs_drt_control(void **cmapp, int op_type)
{
	struct vfs_drt_clustermap *cmap;

	/* sanity */
	if ((cmapp == NULL) || (*cmapp == NULL))
		return(KERN_FAILURE);
	cmap = *cmapp;

	switch (op_type) {
	case 0:
		/* emit stats into trace buffer */
		vfs_drt_trace(cmap, DRT_DEBUG_SCMDATA,
			      cmap->scm_modulus,
			      cmap->scm_buckets,
			      cmap->scm_lastclean,
			      cmap->scm_iskips);

		vfs_drt_free_map(cmap);
		*cmapp = NULL;
	        break;

	case 1:
	        cmap->scm_lastclean = 0;
	        break;
	}
	return(KERN_SUCCESS);
}