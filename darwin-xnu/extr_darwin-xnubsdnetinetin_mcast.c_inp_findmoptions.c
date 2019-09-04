#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct ip_moptions {int imo_multicast_vif; int imo_max_memberships; struct in_mfilter* imo_mfilters; struct in_multi** imo_membership; scalar_t__ imo_num_memberships; int /*<<< orphan*/  imo_multicast_loop; int /*<<< orphan*/  imo_multicast_ttl; TYPE_1__ imo_multicast_addr; int /*<<< orphan*/ * imo_multicast_ifp; } ;
struct inpcb {struct ip_moptions* inp_moptions; } ;
struct in_multi {int dummy; } ;
struct in_mfilter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMO_ADDREF (struct ip_moptions*) ; 
 int /*<<< orphan*/  IMO_REMREF (struct ip_moptions*) ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  IP_DEFAULT_MULTICAST_TTL ; 
 int IP_MIN_MEMBERSHIPS ; 
 int /*<<< orphan*/  MCAST_EXCLUDE ; 
 int /*<<< orphan*/  MCAST_UNDEFINED ; 
 int /*<<< orphan*/  M_INMFILTER ; 
 int /*<<< orphan*/  M_IPMOPTS ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  _FREE (struct in_multi**,int /*<<< orphan*/ ) ; 
 void* _MALLOC (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  imf_init (struct in_mfilter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_mcast_loop ; 
 struct ip_moptions* ip_allocmoptions (int) ; 

__attribute__((used)) static struct ip_moptions *
inp_findmoptions(struct inpcb *inp)
{
	struct ip_moptions	 *imo;
	struct in_multi		**immp;
	struct in_mfilter	 *imfp;
	size_t			  idx;

	if ((imo = inp->inp_moptions) != NULL) {
		IMO_ADDREF(imo);	/* for caller */
		return (imo);
	}

	imo = ip_allocmoptions(M_WAITOK);
	if (imo == NULL)
		return (NULL);

	immp = _MALLOC(sizeof (*immp) * IP_MIN_MEMBERSHIPS, M_IPMOPTS,
	    M_WAITOK | M_ZERO);
	if (immp == NULL) {
		IMO_REMREF(imo);
		return (NULL);
	}

	imfp = _MALLOC(sizeof (struct in_mfilter) * IP_MIN_MEMBERSHIPS,
	    M_INMFILTER, M_WAITOK | M_ZERO);
	if (imfp == NULL) {
		_FREE(immp, M_IPMOPTS);
		IMO_REMREF(imo);
		return (NULL);
	}

	imo->imo_multicast_ifp = NULL;
	imo->imo_multicast_addr.s_addr = INADDR_ANY;
	imo->imo_multicast_vif = -1;
	imo->imo_multicast_ttl = IP_DEFAULT_MULTICAST_TTL;
	imo->imo_multicast_loop = in_mcast_loop;
	imo->imo_num_memberships = 0;
	imo->imo_max_memberships = IP_MIN_MEMBERSHIPS;
	imo->imo_membership = immp;

	/* Initialize per-group source filters. */
	for (idx = 0; idx < IP_MIN_MEMBERSHIPS; idx++)
		imf_init(&imfp[idx], MCAST_UNDEFINED, MCAST_EXCLUDE);

	imo->imo_mfilters = imfp;
	inp->inp_moptions = imo; /* keep reference from ip_allocmoptions() */
	IMO_ADDREF(imo);	/* for caller */

	return (imo);
}