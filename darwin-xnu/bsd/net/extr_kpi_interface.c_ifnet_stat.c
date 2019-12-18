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
struct ifnet_stats_param {int /*<<< orphan*/  no_protocol; int /*<<< orphan*/  dropped; int /*<<< orphan*/  collisions; int /*<<< orphan*/  errors_out; int /*<<< orphan*/  multicasts_out; int /*<<< orphan*/  bytes_out; int /*<<< orphan*/  packets_out; int /*<<< orphan*/  errors_in; int /*<<< orphan*/  multicasts_in; int /*<<< orphan*/  bytes_in; int /*<<< orphan*/  packets_in; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifi_noproto; int /*<<< orphan*/  ifi_iqdrops; int /*<<< orphan*/  ifi_collisions; int /*<<< orphan*/  ifi_oerrors; int /*<<< orphan*/  ifi_omcasts; int /*<<< orphan*/  ifi_obytes; int /*<<< orphan*/  ifi_opackets; int /*<<< orphan*/  ifi_ierrors; int /*<<< orphan*/  ifi_imcasts; int /*<<< orphan*/  ifi_ibytes; int /*<<< orphan*/  ifi_ipackets; } ;
struct ifnet {scalar_t__ if_data_threshold; TYPE_1__ if_data; } ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  atomic_get_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifnet_notify_data_threshold (struct ifnet*) ; 

errno_t
ifnet_stat(struct ifnet *ifp, struct ifnet_stats_param *s)
{
	if (ifp == NULL)
		return (EINVAL);

	atomic_get_64(s->packets_in, &ifp->if_data.ifi_ipackets);
	atomic_get_64(s->bytes_in, &ifp->if_data.ifi_ibytes);
	atomic_get_64(s->multicasts_in, &ifp->if_data.ifi_imcasts);
	atomic_get_64(s->errors_in, &ifp->if_data.ifi_ierrors);

	atomic_get_64(s->packets_out, &ifp->if_data.ifi_opackets);
	atomic_get_64(s->bytes_out, &ifp->if_data.ifi_obytes);
	atomic_get_64(s->multicasts_out, &ifp->if_data.ifi_omcasts);
	atomic_get_64(s->errors_out, &ifp->if_data.ifi_oerrors);

	atomic_get_64(s->collisions, &ifp->if_data.ifi_collisions);
	atomic_get_64(s->dropped, &ifp->if_data.ifi_iqdrops);
	atomic_get_64(s->no_protocol, &ifp->if_data.ifi_noproto);

	if (ifp->if_data_threshold != 0)
		ifnet_notify_data_threshold(ifp);

	return (0);
}