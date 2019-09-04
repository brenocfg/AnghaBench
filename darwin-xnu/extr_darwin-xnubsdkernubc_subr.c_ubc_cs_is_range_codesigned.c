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
typedef  int /*<<< orphan*/ * vnode_t ;
struct cs_blob {scalar_t__ csb_end_offset; scalar_t__ csb_base_offset; scalar_t__ csb_start_offset; } ;
typedef  scalar_t__ mach_vm_size_t ;
typedef  scalar_t__ mach_vm_offset_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 struct cs_blob* ubc_cs_blob_get (int /*<<< orphan*/ *,int,scalar_t__) ; 

boolean_t
ubc_cs_is_range_codesigned(
	vnode_t			vp,
	mach_vm_offset_t	start,
	mach_vm_size_t		size)
{
	struct cs_blob		*csblob;
	mach_vm_offset_t	blob_start;
	mach_vm_offset_t	blob_end;

	if (vp == NULL) {
		/* no file: no code signature */
		return FALSE;
	}
	if (size == 0) {
		/* no range: no code signature */
		return FALSE;
	}
	if (start + size < start) {
		/* overflow */
		return FALSE;
	}

	csblob = ubc_cs_blob_get(vp, -1, start);
	if (csblob == NULL) {
		return FALSE;
	}

	/*
	 * We currently check if the range is covered by a single blob,
	 * which should always be the case for the dyld shared cache.
	 * If we ever want to make this routine handle other cases, we
	 * would have to iterate if the blob does not cover the full range.
	 */
	blob_start = (mach_vm_offset_t) (csblob->csb_base_offset +
					 csblob->csb_start_offset);
	blob_end = (mach_vm_offset_t) (csblob->csb_base_offset +
				       csblob->csb_end_offset);
	if (blob_start > start || blob_end < (start + size)) {
		/* range not fully covered by this code-signing blob */
		return FALSE;
	}

	return TRUE;
}