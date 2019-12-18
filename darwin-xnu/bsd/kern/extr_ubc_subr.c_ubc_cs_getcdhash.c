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
typedef  int /*<<< orphan*/  vnode_t ;
struct cs_blob {scalar_t__ csb_base_offset; scalar_t__ csb_start_offset; scalar_t__ csb_end_offset; int /*<<< orphan*/  csb_cdhash; struct cs_blob* csb_next; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int EBADEXEC ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 struct cs_blob* ubc_get_cs_blobs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_unlock (int /*<<< orphan*/ ) ; 

int
ubc_cs_getcdhash(
	vnode_t		vp,
	off_t		offset,
	unsigned char	*cdhash)
{
	struct cs_blob	*blobs, *blob;
	off_t		rel_offset;
	int		ret;

	vnode_lock(vp);

	blobs = ubc_get_cs_blobs(vp);
	for (blob = blobs;
	     blob != NULL;
	     blob = blob->csb_next) {
		/* compute offset relative to this blob */
		rel_offset = offset - blob->csb_base_offset;
		if (rel_offset >= blob->csb_start_offset &&
		    rel_offset < blob->csb_end_offset) {
			/* this blob does cover our "offset" ! */
			break;
		}
	}

	if (blob == NULL) {
		/* we didn't find a blob covering "offset" */
		ret = EBADEXEC; /* XXX any better error ? */
	} else {
		/* get the SHA1 hash of that blob */
		bcopy(blob->csb_cdhash, cdhash, sizeof (blob->csb_cdhash));
		ret = 0;
	}

	vnode_unlock(vp);

	return ret;
}