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
struct vnode {struct ubc_info* v_ubcinfo; } ;
struct ubc_info {struct cs_blob* cs_blobs; } ;
struct cs_blob {int csb_cpu_type; int csb_base_offset; int csb_start_offset; int csb_end_offset; struct cs_blob* csb_next; } ;
typedef  int off_t ;
typedef  int cpu_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  UBCINFOEXISTS (struct vnode*) ; 
 int /*<<< orphan*/  vnode_lock_spin (struct vnode*) ; 
 int /*<<< orphan*/  vnode_unlock (struct vnode*) ; 

struct cs_blob *
ubc_cs_blob_get(
	struct vnode	*vp,
	cpu_type_t	cputype,
	off_t		offset)
{
	struct ubc_info	*uip;
	struct cs_blob	*blob;
	off_t offset_in_blob;

	vnode_lock_spin(vp);

	if (! UBCINFOEXISTS(vp)) {
		blob = NULL;
		goto out;
	}

	uip = vp->v_ubcinfo;
	for (blob = uip->cs_blobs;
	     blob != NULL;
	     blob = blob->csb_next) {
		if (cputype != -1 && blob->csb_cpu_type == cputype) {
			break;
		}
		if (offset != -1) {
			offset_in_blob = offset - blob->csb_base_offset;
			if (offset_in_blob >= blob->csb_start_offset &&
			    offset_in_blob < blob->csb_end_offset) {
				/* our offset is covered by this blob */
				break;
			}
		}
	}

out:
	vnode_unlock(vp);

	return blob;
}