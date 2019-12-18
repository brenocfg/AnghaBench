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
struct ip6_moptions {int im6o_max_memberships; struct in6_mfilter* im6o_mfilters; struct in6_multi** im6o_membership; scalar_t__ im6o_num_memberships; int /*<<< orphan*/  im6o_multicast_loop; int /*<<< orphan*/  im6o_multicast_hlim; int /*<<< orphan*/ * im6o_multicast_ifp; } ;
struct inpcb {struct ip6_moptions* in6p_moptions; } ;
struct in6_multi {int dummy; } ;
struct in6_mfilter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IM6O_ADDREF (struct ip6_moptions*) ; 
 int /*<<< orphan*/  IM6O_REMREF (struct ip6_moptions*) ; 
 int IPV6_MIN_MEMBERSHIPS ; 
 int /*<<< orphan*/  MCAST_EXCLUDE ; 
 int /*<<< orphan*/  MCAST_UNDEFINED ; 
 int /*<<< orphan*/  M_IN6MFILTER ; 
 int /*<<< orphan*/  M_IP6MOPTS ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  _FREE (struct in6_multi**,int /*<<< orphan*/ ) ; 
 void* _MALLOC (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  im6f_init (struct in6_mfilter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6_mcast_loop ; 
 struct ip6_moptions* ip6_allocmoptions (int) ; 
 int /*<<< orphan*/  ip6_defmcasthlim ; 

__attribute__((used)) static struct ip6_moptions *
in6p_findmoptions(struct inpcb *inp)
{
	struct ip6_moptions	 *imo;
	struct in6_multi	**immp;
	struct in6_mfilter	 *imfp;
	size_t			  idx;

	if ((imo = inp->in6p_moptions) != NULL) {
		IM6O_ADDREF(imo);	/* for caller */
		return (imo);
	}

	imo = ip6_allocmoptions(M_WAITOK);
	if (imo == NULL)
		return (NULL);

	immp = _MALLOC(sizeof (*immp) * IPV6_MIN_MEMBERSHIPS, M_IP6MOPTS,
	    M_WAITOK | M_ZERO);
	if (immp == NULL) {
		IM6O_REMREF(imo);
		return (NULL);
	}

	imfp = _MALLOC(sizeof (struct in6_mfilter) * IPV6_MIN_MEMBERSHIPS,
	    M_IN6MFILTER, M_WAITOK | M_ZERO);
	if (imfp == NULL) {
		_FREE(immp, M_IP6MOPTS);
		IM6O_REMREF(imo);
		return (NULL);
	}

	imo->im6o_multicast_ifp = NULL;
	imo->im6o_multicast_hlim = ip6_defmcasthlim;
	imo->im6o_multicast_loop = in6_mcast_loop;
	imo->im6o_num_memberships = 0;
	imo->im6o_max_memberships = IPV6_MIN_MEMBERSHIPS;
	imo->im6o_membership = immp;

	/* Initialize per-group source filters. */
	for (idx = 0; idx < IPV6_MIN_MEMBERSHIPS; idx++)
		im6f_init(&imfp[idx], MCAST_UNDEFINED, MCAST_EXCLUDE);

	imo->im6o_mfilters = imfp;
	inp->in6p_moptions = imo; /* keep reference from ip6_allocmoptions() */
	IM6O_ADDREF(imo);	/* for caller */

	return (imo);
}