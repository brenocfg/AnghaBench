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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_long ;
struct utun_pcb {scalar_t__ utun_slot_size; int /*<<< orphan*/  utun_use_netif; } ;
struct ifreq {int /*<<< orphan*/  ifr_mtu; } ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
#define  SIOCSIFFLAGS 129 
#define  SIOCSIFMTU 128 
 scalar_t__ UTUN_IF_HEADROOM_SIZE ; 
 int /*<<< orphan*/  ifnet_set_mtu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct utun_pcb* ifnet_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static errno_t
utun_ioctl(ifnet_t interface,
		   u_long command,
		   void *data)
{
#if UTUN_NEXUS
	struct utun_pcb	*pcb = ifnet_softc(interface);
#endif
	errno_t	result = 0;
	
	switch(command) {
		case SIOCSIFMTU: {
#if UTUN_NEXUS
			if (pcb->utun_use_netif) {
				// Make sure we can fit packets in the channel buffers
				// Allow for the headroom in the slot
				if (((uint64_t)((struct ifreq*)data)->ifr_mtu) + UTUN_IF_HEADROOM_SIZE > pcb->utun_slot_size) {
					result = EINVAL;
				} else {
					ifnet_set_mtu(interface, (uint32_t)((struct ifreq*)data)->ifr_mtu);
				}
			} else
#endif // UTUN_NEXUS
			{
				ifnet_set_mtu(interface, ((struct ifreq*)data)->ifr_mtu);
			}
			break;
		}
			
		case SIOCSIFFLAGS:
			/* ifioctl() takes care of it */
			break;
			
		default:
			result = EOPNOTSUPP;
	}
	
	return result;
}