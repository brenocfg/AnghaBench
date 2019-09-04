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
typedef  struct vnode* vnode_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct vnode {int dummy; } ;
struct fileglob {scalar_t__ fg_data; } ;
struct cs_blob {int /*<<< orphan*/ * csb_cdhash; } ;

/* Variables and functions */
 size_t CS_CDHASH_LEN ; 
 scalar_t__ DTYPE_VNODE ; 
 scalar_t__ FILEGLOB_DTYPE (struct fileglob*) ; 
 struct cs_blob* ubc_cs_blob_get (struct vnode*,int,int /*<<< orphan*/ ) ; 

uint8_t *
csfg_get_cdhash(struct fileglob *fg, uint64_t offset, size_t *cdhash_size)
{
	vnode_t vp;

	if (FILEGLOB_DTYPE(fg) != DTYPE_VNODE)
		return NULL;

	vp = (struct vnode *)fg->fg_data;
	if (vp == NULL)
		return NULL;

	struct cs_blob *csblob = NULL;
	if ((csblob = ubc_cs_blob_get(vp, -1, offset)) == NULL) 
		return NULL;

	if (cdhash_size)
		*cdhash_size = CS_CDHASH_LEN;

	return csblob->csb_cdhash;
}