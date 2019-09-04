#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sysctl_req {int oldlen; int /*<<< orphan*/  oldptr; int /*<<< orphan*/  newptr; } ;
struct TYPE_4__ {int /*<<< orphan*/  packets; } ;
struct TYPE_5__ {TYPE_1__ ifcq_dropcnt; } ;
struct ifnet {int if_linkmiblen; struct ifmibdata_supplemental* if_linkmib; TYPE_2__ if_snd; int /*<<< orphan*/  if_data; int /*<<< orphan*/  if_flags; int /*<<< orphan*/  if_pcount; } ;
struct ifmibdata_supplemental {int /*<<< orphan*/  ifmd_rxpoll_stats; int /*<<< orphan*/  ifmd_packet_stats; int /*<<< orphan*/  ifmd_data_extended; int /*<<< orphan*/  ifmd_traffic_class; int /*<<< orphan*/  ifmd_snd_drops; int /*<<< orphan*/  ifmd_snd_maxlen; int /*<<< orphan*/  ifmd_snd_len; int /*<<< orphan*/  ifmd_data; int /*<<< orphan*/  ifmd_flags; int /*<<< orphan*/  ifmd_pcount; int /*<<< orphan*/  ifmd_name; } ;
struct ifmibdata {int /*<<< orphan*/  ifmd_rxpoll_stats; int /*<<< orphan*/  ifmd_packet_stats; int /*<<< orphan*/  ifmd_data_extended; int /*<<< orphan*/  ifmd_traffic_class; int /*<<< orphan*/  ifmd_snd_drops; int /*<<< orphan*/  ifmd_snd_maxlen; int /*<<< orphan*/  ifmd_snd_len; int /*<<< orphan*/  ifmd_data; int /*<<< orphan*/  ifmd_flags; int /*<<< orphan*/  ifmd_pcount; int /*<<< orphan*/  ifmd_name; } ;
typedef  int /*<<< orphan*/  ifmd ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IFCQ_LEN (TYPE_2__*) ; 
 int /*<<< orphan*/  IFCQ_MAXLEN (TYPE_2__*) ; 
#define  IFDATA_GENERAL 130 
#define  IFDATA_LINKSPECIFIC 129 
#define  IFDATA_SUPPLEMENTAL 128 
 int MIN (int,int) ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_ZERO ; 
 int SYSCTL_OUT (struct sysctl_req*,struct ifmibdata_supplemental*,int) ; 
 int /*<<< orphan*/  USER_ADDR_NULL ; 
 int /*<<< orphan*/  _FREE (struct ifmibdata_supplemental*,int /*<<< orphan*/ ) ; 
 struct ifmibdata_supplemental* _MALLOC (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (struct ifmibdata_supplemental*,int) ; 
 int /*<<< orphan*/  if_copy_data_extended (struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_copy_packet_stats (struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_copy_rxpoll_stats (struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_copy_traffic_class (struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_data_internal_to_if_data64 (struct ifnet*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* if_name (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_is_attached (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

int
make_ifmibdata(struct ifnet *ifp, int *name, struct sysctl_req *req)
{
	struct ifmibdata	ifmd;
	int error = 0;

	switch(name[1]) {
	default:
		error = ENOENT;
		break;

	case IFDATA_GENERAL:
		bzero(&ifmd, sizeof(ifmd));
		/*
		 * Make sure the interface is in use
		 */
		if (ifnet_is_attached(ifp, 0)) {
			snprintf(ifmd.ifmd_name, sizeof(ifmd.ifmd_name), "%s",
				if_name(ifp));

#define COPY(fld) ifmd.ifmd_##fld = ifp->if_##fld
			COPY(pcount);
			COPY(flags);
			if_data_internal_to_if_data64(ifp, &ifp->if_data, &ifmd.ifmd_data);
#undef COPY
			ifmd.ifmd_snd_len = IFCQ_LEN(&ifp->if_snd);
			ifmd.ifmd_snd_maxlen = IFCQ_MAXLEN(&ifp->if_snd);
			ifmd.ifmd_snd_drops = ifp->if_snd.ifcq_dropcnt.packets;
		}
		error = SYSCTL_OUT(req, &ifmd, sizeof ifmd);
		if (error || !req->newptr)
			break;

#ifdef IF_MIB_WR
		error = SYSCTL_IN(req, &ifmd, sizeof ifmd);
		if (error)
			break;

#define DONTCOPY(fld) ifmd.ifmd_data.ifi_##fld = ifp->if_data.ifi_##fld
		DONTCOPY(type);
		DONTCOPY(physical);
		DONTCOPY(addrlen);
		DONTCOPY(hdrlen);
		DONTCOPY(mtu);
		DONTCOPY(metric);
		DONTCOPY(baudrate);
#undef DONTCOPY
#define COPY(fld) ifp->if_##fld = ifmd.ifmd_##fld
		COPY(data);
		ifp->if_snd.ifq_maxlen = ifmd.ifmd_snd_maxlen;
		ifp->if_snd.ifq_drops = ifmd.ifmd_snd_drops;
#undef COPY
#endif /* IF_MIB_WR */
		break;

	case IFDATA_LINKSPECIFIC:
		error = SYSCTL_OUT(req, ifp->if_linkmib, ifp->if_linkmiblen);
		if (error || !req->newptr)
			break;

#ifdef IF_MIB_WR
		error = SYSCTL_IN(req, ifp->if_linkmib, ifp->if_linkmiblen);
		if (error)
			break;
#endif /* IF_MIB_WR */
		break;

	case IFDATA_SUPPLEMENTAL: {
		struct ifmibdata_supplemental *ifmd_supp;

		if ((ifmd_supp = _MALLOC(sizeof (*ifmd_supp), M_TEMP,
		    M_NOWAIT | M_ZERO)) == NULL) {
			error = ENOMEM;
			break;
		}

		if_copy_traffic_class(ifp, &ifmd_supp->ifmd_traffic_class);
		if_copy_data_extended(ifp, &ifmd_supp->ifmd_data_extended);
		if_copy_packet_stats(ifp, &ifmd_supp->ifmd_packet_stats);
		if_copy_rxpoll_stats(ifp, &ifmd_supp->ifmd_rxpoll_stats);

		if (req->oldptr == USER_ADDR_NULL)
			req->oldlen = sizeof (*ifmd_supp);

		error = SYSCTL_OUT(req, ifmd_supp, MIN(sizeof (*ifmd_supp),
		    req->oldlen));

		_FREE(ifmd_supp, M_TEMP);
		break;
	}
	}

	return error;
}