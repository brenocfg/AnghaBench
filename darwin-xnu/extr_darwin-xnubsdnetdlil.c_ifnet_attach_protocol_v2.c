#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct ifnet_attach_proto_param_v2 {int /*<<< orphan*/  demux_count; int /*<<< orphan*/  demux_list; int /*<<< orphan*/  send_arp; int /*<<< orphan*/  resolve; int /*<<< orphan*/  detached; int /*<<< orphan*/  ioctl; int /*<<< orphan*/  event; int /*<<< orphan*/  pre_output; int /*<<< orphan*/  input; } ;
struct TYPE_3__ {int /*<<< orphan*/  send_arp; int /*<<< orphan*/  resolve_multi; int /*<<< orphan*/  detached; int /*<<< orphan*/  ioctl; int /*<<< orphan*/  event; int /*<<< orphan*/  pre_output; int /*<<< orphan*/  input; } ;
struct TYPE_4__ {TYPE_1__ v2; } ;
struct if_proto {TYPE_2__ kpi; int /*<<< orphan*/  proto_kpi; scalar_t__ protocol_family; int /*<<< orphan*/ * ifp; } ;
typedef  scalar_t__ protocol_family_t ;
typedef  int /*<<< orphan*/ * ifnet_t ;
typedef  int errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLIL_PRINTF (char*,char*,scalar_t__,int) ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  IFF_UP ; 
 int /*<<< orphan*/  SIOCSIFFLAGS ; 
 int /*<<< orphan*/  bzero (struct if_proto*,int) ; 
 int /*<<< orphan*/  dlif_proto_zone ; 
 int dlil_attach_protocol_internal (struct if_proto*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dlil_post_sifflags_msg (int /*<<< orphan*/ *) ; 
 scalar_t__ dlil_verbose ; 
 char* if_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifnet_head_done () ; 
 int /*<<< orphan*/  ifnet_head_lock_shared () ; 
 int /*<<< orphan*/  ifnet_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifnet_lookup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifnet_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kProtoKPI_v2 ; 
 int /*<<< orphan*/  printf (char*,char*,scalar_t__,int) ; 
 struct if_proto* zalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct if_proto*) ; 

errno_t
ifnet_attach_protocol_v2(ifnet_t ifp, protocol_family_t protocol,
    const struct ifnet_attach_proto_param_v2 *proto_details)
{
	int retval = 0;
	struct if_proto  *ifproto = NULL;
	uint32_t proto_count = 0;

	ifnet_head_lock_shared();
	if (ifp == NULL || protocol == 0 || proto_details == NULL) {
		retval = EINVAL;
		goto end;
	}
	/* Check that the interface is in the global list */
	if (!ifnet_lookup(ifp)) {
		retval = ENXIO;
		goto end;
	}

	ifproto = zalloc(dlif_proto_zone);
	if (ifproto == NULL) {
		retval = ENOMEM;
		goto end;
	}
	bzero(ifproto, sizeof(*ifproto));

	/* refcnt held above during lookup */
	ifproto->ifp = ifp;
	ifproto->protocol_family = protocol;
	ifproto->proto_kpi = kProtoKPI_v2;
	ifproto->kpi.v2.input = proto_details->input;
	ifproto->kpi.v2.pre_output = proto_details->pre_output;
	ifproto->kpi.v2.event = proto_details->event;
	ifproto->kpi.v2.ioctl = proto_details->ioctl;
	ifproto->kpi.v2.detached = proto_details->detached;
	ifproto->kpi.v2.resolve_multi = proto_details->resolve;
	ifproto->kpi.v2.send_arp = proto_details->send_arp;

	retval = dlil_attach_protocol_internal(ifproto,
			proto_details->demux_list, proto_details->demux_count,
			&proto_count);

end:
	if (retval != 0 && retval != EEXIST && ifp != NULL) {
		DLIL_PRINTF("%s: failed to attach v2 protocol %d (err=%d)\n",
		    if_name(ifp), protocol, retval);
	} else {
		if (dlil_verbose) {
			printf("%s: attached v2 protocol %d (count = %d)\n",
			       if_name(ifp),
			       protocol, proto_count);
		}
	}
	ifnet_head_done();
	if (retval == 0) {
		/*
		 * A protocol has been attached, mark the interface up.
		 * This used to be done by configd.KernelEventMonitor, but that
		 * is inherently prone to races (rdar://problem/30810208).
		 */
		(void) ifnet_set_flags(ifp, IFF_UP, IFF_UP);
		(void) ifnet_ioctl(ifp, 0, SIOCSIFFLAGS, NULL);
		dlil_post_sifflags_msg(ifp);
	} else if (ifproto != NULL) {
		zfree(dlif_proto_zone, ifproto);
	}
	return (retval);
}