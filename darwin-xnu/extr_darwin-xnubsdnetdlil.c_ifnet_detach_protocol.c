#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {void* send_arp; void* resolve_multi; void* ioctl; void* event; void* pre_output; int /*<<< orphan*/  input; } ;
struct TYPE_11__ {void* send_arp; void* resolve_multi; void* ioctl; void* event; void* pre_output; int /*<<< orphan*/  input; } ;
struct TYPE_13__ {TYPE_2__ v2; TYPE_1__ v1; } ;
struct if_proto {scalar_t__ proto_kpi; int detached; TYPE_3__ kpi; int /*<<< orphan*/  protocol_family; } ;
typedef  scalar_t__ protocol_family_t ;
typedef  TYPE_4__* ifnet_t ;
typedef  int errno_t ;
struct TYPE_14__ {int /*<<< orphan*/ * if_proto_hash; int /*<<< orphan*/  (* if_del_proto ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct if_proto*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dlil_verbose ; 
 struct if_proto* find_attached_proto (TYPE_4__*,scalar_t__) ; 
 char* if_name (TYPE_4__*) ; 
 int /*<<< orphan*/  if_proto ; 
 int /*<<< orphan*/  if_proto_free (struct if_proto*) ; 
 int /*<<< orphan*/  ifnet_lock_done (TYPE_4__*) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (TYPE_4__*) ; 
 void* ifproto_media_event ; 
 int /*<<< orphan*/  ifproto_media_input_v1 ; 
 int /*<<< orphan*/  ifproto_media_input_v2 ; 
 void* ifproto_media_ioctl ; 
 void* ifproto_media_preout ; 
 void* ifproto_media_resolve_multi ; 
 void* ifproto_media_send_arp ; 
 scalar_t__ kProtoKPI_v1 ; 
 int /*<<< orphan*/  next_hash ; 
 int /*<<< orphan*/  printf (char*,char*,char*,scalar_t__) ; 
 size_t proto_hash_value (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 

errno_t
ifnet_detach_protocol(ifnet_t ifp, protocol_family_t proto_family)
{
	struct if_proto *proto = NULL;
	int	retval = 0;

	if (ifp == NULL || proto_family == 0) {
		retval = EINVAL;
		goto end;
	}

	ifnet_lock_exclusive(ifp);
	/* callee holds a proto refcnt upon success */
	proto = find_attached_proto(ifp, proto_family);
	if (proto == NULL) {
		retval = ENXIO;
		ifnet_lock_done(ifp);
		goto end;
	}

	/* call family module del_proto */
	if (ifp->if_del_proto)
		ifp->if_del_proto(ifp, proto->protocol_family);

	SLIST_REMOVE(&ifp->if_proto_hash[proto_hash_value(proto_family)],
	    proto, if_proto, next_hash);

	if (proto->proto_kpi == kProtoKPI_v1) {
		proto->kpi.v1.input = ifproto_media_input_v1;
		proto->kpi.v1.pre_output = ifproto_media_preout;
		proto->kpi.v1.event = ifproto_media_event;
		proto->kpi.v1.ioctl = ifproto_media_ioctl;
		proto->kpi.v1.resolve_multi = ifproto_media_resolve_multi;
		proto->kpi.v1.send_arp = ifproto_media_send_arp;
	} else {
		proto->kpi.v2.input = ifproto_media_input_v2;
		proto->kpi.v2.pre_output = ifproto_media_preout;
		proto->kpi.v2.event = ifproto_media_event;
		proto->kpi.v2.ioctl = ifproto_media_ioctl;
		proto->kpi.v2.resolve_multi = ifproto_media_resolve_multi;
		proto->kpi.v2.send_arp = ifproto_media_send_arp;
	}
	proto->detached = 1;
	ifnet_lock_done(ifp);

	if (dlil_verbose) {
		printf("%s: detached %s protocol %d\n", if_name(ifp),
		    (proto->proto_kpi == kProtoKPI_v1) ?
		    "v1" : "v2", proto_family);
	}

	/* release proto refcnt held during protocol attach */
	if_proto_free(proto);

	/*
	 * Release proto refcnt held during lookup; the rest of
	 * protocol detach steps will happen when the last proto
	 * reference is released.
	 */
	if_proto_free(proto);

end:
	return (retval);
}