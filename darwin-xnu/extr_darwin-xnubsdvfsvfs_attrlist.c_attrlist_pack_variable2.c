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
struct attrreference {char* attr_dataoffset; scalar_t__ attr_length; } ;
struct _attrlist_buf {char* varcursor; int fixedcursor; char* allocated; int base; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  ar ;

/* Variables and functions */
 int /*<<< orphan*/  attrlist_pack_fixed (struct _attrlist_buf*,struct attrreference*,int) ; 
 int /*<<< orphan*/  bcopy (void const*,char*,scalar_t__) ; 
 scalar_t__ lmin (scalar_t__,char*) ; 
 scalar_t__ roundup (uintptr_t,int) ; 

__attribute__((used)) static void
attrlist_pack_variable2(struct _attrlist_buf *ab, const void *source, ssize_t count, 
		const void *ext, ssize_t extcount) 
{
	/* Use ssize_t's for pointer math ease */
	struct attrreference ar;
	ssize_t fit;

	/*
	 * Pack the fixed-width component to the variable object. 
	 * Note that we may be able to pack the fixed width attref, but not
	 * the variable (if there's no room).
	 */
	ar.attr_dataoffset = ab->varcursor - ab->fixedcursor;
	ar.attr_length = count + extcount;
	attrlist_pack_fixed(ab, &ar, sizeof(ar));

	/* 
	 * Use an lmin() to do a signed comparison. We use a signed comparison
	 * to detect the 'out of memory' conditions as described above in the
	 * fixed width check above.
	 *
	 * Then pack the first variable attribute as space allows.  Note that we advance
	 * the variable cursor only if we we had some available space. 
	 */
	fit = lmin(count, ab->allocated - (ab->varcursor - ab->base));
	if (fit > 0) {
		if (source != NULL) {
			bcopy(source, ab->varcursor, fit);
		}
		ab->varcursor += fit;
	}

	/* Compute the available space for the second attribute */
	fit = lmin(extcount, ab->allocated - (ab->varcursor - ab->base));
	if (fit > 0) {
		/* Copy in data for the second attribute (if needed) if there is room */
		if (ext != NULL) {
			bcopy(ext, ab->varcursor, fit);
		}
		ab->varcursor += fit;
	}
	/* always move in increments of 4 */
	ab->varcursor = (char *)roundup((uintptr_t)ab->varcursor, 4);
}