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
struct route {int /*<<< orphan*/ * ro_srcia; int /*<<< orphan*/ * ro_rt; int /*<<< orphan*/ * ro_lle; int /*<<< orphan*/  ro_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFA_REMREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LLE_REMREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcopy (struct route*,struct route*,size_t) ; 
 int /*<<< orphan*/  rtfree (int /*<<< orphan*/ *) ; 

void
route_copyin(struct route *src, struct route *dst, size_t length)
{
	/*
	 * No cached route at the destination?
	 * If none, then remove old references if present
	 * and copy entire src route.
	 */
	if (dst->ro_rt == NULL) {
		/*
		 * Ditch the cached link layer reference (dst)
		 * since we're about to take everything there is in src
		 */
		if (dst->ro_lle != NULL)
			LLE_REMREF(dst->ro_lle);
		/*
		 * Ditch the address in the cached copy (dst) since
		 * we're about to take everything there is in src.
		 */
		if (dst->ro_srcia != NULL)
			IFA_REMREF(dst->ro_srcia);
		/*
		 * Copy everything (rt, ro_lle, srcia, flags, dst) from src; the
		 * references to rt and/or srcia were held at the time
		 * of storage and are kept intact.
		 */
		bcopy(src, dst, length);
		goto done;
	}

	/*
	 * We know dst->ro_rt is not NULL here.
	 * If the src->ro_rt is the same, update ro_lle, srcia and flags
	 * and ditch the route in the local copy.
	 */
	if (dst->ro_rt == src->ro_rt) {
		dst->ro_flags = src->ro_flags;

		if (dst->ro_lle != src->ro_lle) {
			if (dst->ro_lle != NULL)
				LLE_REMREF(dst->ro_lle);
			dst->ro_lle = src->ro_lle;
		} else if (src->ro_lle != NULL) {
			LLE_REMREF(src->ro_lle);
		}

		if (dst->ro_srcia != src->ro_srcia) {
			if (dst->ro_srcia != NULL)
				IFA_REMREF(dst->ro_srcia);
			dst->ro_srcia = src->ro_srcia;
		} else if (src->ro_srcia != NULL) {
			IFA_REMREF(src->ro_srcia);
		}
		rtfree(src->ro_rt);
		goto done;
	}

	/*
	 * If they are dst's ro_rt is not equal to src's,
	 * and src'd rt is not NULL, then remove old references
	 * if present and copy entire src route.
	 */
	if (src->ro_rt != NULL) {
		rtfree(dst->ro_rt);

		if (dst->ro_lle != NULL)
			LLE_REMREF(dst->ro_lle);
		if (dst->ro_srcia != NULL)
			IFA_REMREF(dst->ro_srcia);
		bcopy(src, dst, length);
		goto done;
	}

	/*
	 * Here, dst's cached route is not NULL but source's is.
	 * Just get rid of all the other cached reference in src.
	 */
	if (src->ro_srcia != NULL) {
		/*
		 * Ditch src address in the local copy (src) since we're
		 * not caching the route entry anyway (ro_rt is NULL).
		 */
		IFA_REMREF(src->ro_srcia);
	}
	if (src->ro_lle != NULL) {
		/*
		 * Ditch cache lle in the local copy (src) since we're
		 * not caching the route anyway (ro_rt is NULL).
		 */
		LLE_REMREF(src->ro_lle);
	}
done:
	/* This function consumes the references on src */
	src->ro_lle = NULL;
	src->ro_rt = NULL;
	src->ro_srcia = NULL;
}