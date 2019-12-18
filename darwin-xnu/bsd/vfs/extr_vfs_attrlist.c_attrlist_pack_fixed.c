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
struct _attrlist_buf {scalar_t__ fixedcursor; scalar_t__ base; scalar_t__ allocated; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (void*,scalar_t__,scalar_t__) ; 
 scalar_t__ lmin (scalar_t__,scalar_t__) ; 
 scalar_t__ roundup (scalar_t__,int) ; 

__attribute__((used)) static void
attrlist_pack_fixed(struct _attrlist_buf *ab, void *source, ssize_t count)
{
	/* 
	 * Use ssize_t for pointer math purposes,
	 * since a ssize_t is a signed long
	 */
	ssize_t	fit;

	/*
	 * Compute the amount of remaining space in the attrlist buffer
	 * based on how much we've used for fixed width fields vs. the
	 * start of the attributes.  
	 * 
	 * If we've still got room, then 'fit' will contain the amount of 
	 * remaining space.  
	 * 
	 * Note that this math is safe because, in the event that the 
	 * fixed-width cursor has moved beyond the end of the buffer,
	 * then, the second input into lmin() below will be negative, and 
	 * we will fail the (fit > 0) check below. 
	 */ 
	fit = lmin(count, ab->allocated - (ab->fixedcursor - ab->base));
	if (fit > 0) {
		/* Copy in as much as we can */
		bcopy(source, ab->fixedcursor, fit);
	}

	/* always move in increments of 4, even if we didn't pack an attribute. */
	ab->fixedcursor += roundup(count, 4);
}