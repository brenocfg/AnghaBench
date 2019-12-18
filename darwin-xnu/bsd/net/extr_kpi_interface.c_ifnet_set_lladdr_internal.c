#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr_dl {size_t sdl_alen; int /*<<< orphan*/  sdl_type; } ;
struct ifaddr {scalar_t__ ifa_addr; } ;
typedef  TYPE_1__* ifnet_t ;
typedef  scalar_t__ errno_t ;
struct TYPE_7__ {size_t if_addrlen; int if_index; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ENXIO ; 
 int /*<<< orphan*/  IFA_LOCK_SPIN (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_UNLOCK (struct ifaddr*) ; 
 int /*<<< orphan*/  INTF_EVENT_CODE_LLADDR_UPDATE ; 
 int /*<<< orphan*/  KEV_DL_LINK_ADDRESS_CHANGED ; 
 int /*<<< orphan*/  KEV_DL_SUBCLASS ; 
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  bcopy (void const*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dlil_post_msg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ifaddr** ifnet_addrs ; 
 int /*<<< orphan*/  ifnet_head_done () ; 
 int /*<<< orphan*/  ifnet_head_lock_shared () ; 
 int /*<<< orphan*/  ifnet_lock_done (TYPE_1__*) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (TYPE_1__*) ; 
 int /*<<< orphan*/  intf_event_enqueue_nwk_wq_entry (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static errno_t
ifnet_set_lladdr_internal(ifnet_t interface, const void *lladdr,
    size_t lladdr_len, u_char new_type, int apply_type)
{
	struct ifaddr *ifa;
	errno_t	error = 0;

	if (interface == NULL)
		return (EINVAL);

	ifnet_head_lock_shared();
	ifnet_lock_exclusive(interface);
	if (lladdr_len != 0 &&
	    (lladdr_len != interface->if_addrlen || lladdr == 0)) {
		ifnet_lock_done(interface);
		ifnet_head_done();
		return (EINVAL);
	}
	ifa = ifnet_addrs[interface->if_index - 1];
	if (ifa != NULL) {
		struct sockaddr_dl *sdl;

		IFA_LOCK_SPIN(ifa);
		sdl = (struct sockaddr_dl *)(void *)ifa->ifa_addr;
		if (lladdr_len != 0) {
			bcopy(lladdr, LLADDR(sdl), lladdr_len);
		} else {
			bzero(LLADDR(sdl), interface->if_addrlen);
		}
		sdl->sdl_alen = lladdr_len;

		if (apply_type) {
			sdl->sdl_type = new_type;
		}
		IFA_UNLOCK(ifa);
	} else {
		error = ENXIO;
	}
	ifnet_lock_done(interface);
	ifnet_head_done();

	/* Generate a kernel event */
	if (error == 0) {
		intf_event_enqueue_nwk_wq_entry(interface, NULL,
		    INTF_EVENT_CODE_LLADDR_UPDATE);
		dlil_post_msg(interface, KEV_DL_SUBCLASS,
		    KEV_DL_LINK_ADDRESS_CHANGED, NULL, 0);
	}

	return (error);
}