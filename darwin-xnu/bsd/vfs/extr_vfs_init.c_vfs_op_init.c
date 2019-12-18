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
struct TYPE_4__ {int vdesc_flags; int vdesc_offset; } ;
struct TYPE_3__ {int /*<<< orphan*/ ** opv_desc_vector_p; } ;

/* Variables and functions */
 int /*<<< orphan*/  DODEBUG (int /*<<< orphan*/ ) ; 
 int VDESC_DISABLED ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_2__** vfs_op_descs ; 
 TYPE_1__** vfs_opv_descs ; 
 int vfs_opv_numops ; 

void
vfs_op_init(void)
{
	int i;

	DODEBUG(printf("Vnode_interface_init.\n"));
	/*
	 * Set all vnode vectors to a well known value.
	 */
	for (i = 0; vfs_opv_descs[i]; i++)
		*(vfs_opv_descs[i]->opv_desc_vector_p) = NULL;
	/*
	 * Figure out how many ops there are by counting the table,
	 * and assign each its offset.
	 */
	for (vfs_opv_numops = 0, i = 0; vfs_op_descs[i]; i++) {
		/* Silently skip known-disabled operations */
		if (vfs_op_descs[i]->vdesc_flags & VDESC_DISABLED) {
			continue;
		}
		vfs_op_descs[i]->vdesc_offset = vfs_opv_numops;
		vfs_opv_numops++;
	}
	DODEBUG(printf ("vfs_opv_numops=%d\n", vfs_opv_numops));
}