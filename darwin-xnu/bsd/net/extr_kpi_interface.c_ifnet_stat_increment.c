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
struct ifnet_stat_increment_param {scalar_t__ packets_in; scalar_t__ bytes_in; scalar_t__ errors_in; scalar_t__ packets_out; scalar_t__ bytes_out; scalar_t__ errors_out; scalar_t__ collisions; scalar_t__ dropped; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifi_iqdrops; int /*<<< orphan*/  ifi_collisions; int /*<<< orphan*/  ifi_oerrors; int /*<<< orphan*/  ifi_obytes; int /*<<< orphan*/  ifi_opackets; int /*<<< orphan*/  ifi_ierrors; int /*<<< orphan*/  ifi_ibytes; int /*<<< orphan*/  ifi_ipackets; } ;
struct ifnet {scalar_t__ if_data_threshold; int /*<<< orphan*/  if_lastchange; TYPE_1__ if_data; } ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  TOUCHLASTCHANGE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_add_64 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ifnet_notify_data_threshold (struct ifnet*) ; 

errno_t
ifnet_stat_increment(struct ifnet *ifp,
    const struct ifnet_stat_increment_param *s)
{
	if (ifp == NULL)
		return (EINVAL);

	if (s->packets_in != 0)
		atomic_add_64(&ifp->if_data.ifi_ipackets, s->packets_in);
	if (s->bytes_in != 0)
		atomic_add_64(&ifp->if_data.ifi_ibytes, s->bytes_in);
	if (s->errors_in != 0)
		atomic_add_64(&ifp->if_data.ifi_ierrors, s->errors_in);

	if (s->packets_out != 0)
		atomic_add_64(&ifp->if_data.ifi_opackets, s->packets_out);
	if (s->bytes_out != 0)
		atomic_add_64(&ifp->if_data.ifi_obytes, s->bytes_out);
	if (s->errors_out != 0)
		atomic_add_64(&ifp->if_data.ifi_oerrors, s->errors_out);

	if (s->collisions != 0)
		atomic_add_64(&ifp->if_data.ifi_collisions, s->collisions);
	if (s->dropped != 0)
		atomic_add_64(&ifp->if_data.ifi_iqdrops, s->dropped);

	/* Touch the last change time. */
	TOUCHLASTCHANGE(&ifp->if_lastchange);

	if (ifp->if_data_threshold != 0)
		ifnet_notify_data_threshold(ifp);

	return (0);
}