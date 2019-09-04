#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ip_moptions {int imo_num_memberships; scalar_t__ imo_max_memberships; TYPE_1__** imo_membership; struct in_mfilter* imo_mfilters; int /*<<< orphan*/  imo_multicast_loop; int /*<<< orphan*/  imo_multicast_ttl; int /*<<< orphan*/  imo_multicast_vif; int /*<<< orphan*/  imo_multicast_ifp; } ;
struct inpcb {int dummy; } ;
struct in_mfilter {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  inm_ifp; int /*<<< orphan*/  inm_addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IMO_LOCK (struct ip_moptions*) ; 
 int /*<<< orphan*/  IMO_REMREF (struct ip_moptions*) ; 
 int /*<<< orphan*/  IMO_UNLOCK (struct ip_moptions*) ; 
 int /*<<< orphan*/  INM_REMREF (TYPE_1__*) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  imf_leave (struct in_mfilter*) ; 
 int /*<<< orphan*/  imf_purge (struct in_mfilter*) ; 
 int imo_grow (struct ip_moptions*,scalar_t__) ; 
 TYPE_1__* in_addmulti (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_leavegroup (TYPE_1__*,struct in_mfilter*) ; 
 struct ip_moptions* inp_findmoptions (struct inpcb*) ; 

int
imo_clone(struct inpcb *from_inp, struct inpcb *to_inp)
{
	int i, err = 0;
	struct ip_moptions *from;
	struct ip_moptions *to;

	from = inp_findmoptions(from_inp);
	if (from == NULL)
		return (ENOMEM); 

	to = inp_findmoptions(to_inp);
	if (to == NULL) {
		IMO_REMREF(from);
		return (ENOMEM);
	}

	IMO_LOCK(from);
	IMO_LOCK(to);

        to->imo_multicast_ifp = from->imo_multicast_ifp;
        to->imo_multicast_vif = from->imo_multicast_vif;
        to->imo_multicast_ttl = from->imo_multicast_ttl;
        to->imo_multicast_loop = from->imo_multicast_loop;

	/*
	 * We're cloning, so drop any existing memberships and source
	 * filters on the destination ip_moptions.
	 */
	for (i = 0; i < to->imo_num_memberships; ++i) {
		struct in_mfilter *imf;

		imf = to->imo_mfilters ? &to->imo_mfilters[i] : NULL;
		if (imf != NULL)
			imf_leave(imf);

		(void) in_leavegroup(to->imo_membership[i], imf);

		if (imf != NULL)
			imf_purge(imf);

		INM_REMREF(to->imo_membership[i]);
		to->imo_membership[i] = NULL;
	}
	to->imo_num_memberships = 0;

	VERIFY(to->imo_max_memberships != 0 && from->imo_max_memberships != 0);
	if (to->imo_max_memberships < from->imo_max_memberships) {
		/*
		 * Ensure source and destination ip_moptions memberships
		 * and source filters arrays are at least equal in size.
		 */
		err = imo_grow(to, from->imo_max_memberships);
		if (err != 0)
			goto done;
	}
	VERIFY(to->imo_max_memberships >= from->imo_max_memberships);

	/*
	 * Source filtering doesn't apply to OpenTransport socket,
	 * so simply hold additional reference count per membership.
	 */
	for (i = 0; i < from->imo_num_memberships; i++) {
		to->imo_membership[i] = 
			in_addmulti(&from->imo_membership[i]->inm_addr,
						from->imo_membership[i]->inm_ifp);
		if (to->imo_membership[i] == NULL)
			break;
		to->imo_num_memberships++;
        }
	VERIFY(to->imo_num_memberships == from->imo_num_memberships);

done:
	IMO_UNLOCK(to);
	IMO_REMREF(to);
	IMO_UNLOCK(from);
	IMO_REMREF(from);

	return (err);
}