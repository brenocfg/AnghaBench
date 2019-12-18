#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u_int8_t ;
struct ifaddr {int /*<<< orphan*/ ** ifa_addr; } ;
typedef  int /*<<< orphan*/  sdlbuf ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  TYPE_1__* ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_6__ {int /*<<< orphan*/  sdl_len; } ;
struct TYPE_5__ {struct ifaddr* if_lladdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EMSGSIZE ; 
 int /*<<< orphan*/  IFA_LOCK_SPIN (struct ifaddr*) ; 
 int /*<<< orphan*/  IFA_UNLOCK (struct ifaddr*) ; 
 TYPE_3__* SDL (int /*<<< orphan*/ **) ; 
 int SOCK_MAXADDRLEN ; 
 int /*<<< orphan*/  _CASSERT (int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,void*,size_t) ; 
 int /*<<< orphan*/  bzero (void*,size_t) ; 
 int /*<<< orphan*/ * dlil_ifaddr_bytes (TYPE_3__*,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static errno_t
ifnet_lladdr_copy_bytes_internal(ifnet_t interface, void *lladdr,
    size_t lladdr_len, kauth_cred_t *credp)
{
	const u_int8_t *bytes;
	size_t bytes_len;
	struct ifaddr *ifa;
	uint8_t sdlbuf[SOCK_MAXADDRLEN + 1];
	errno_t error = 0;

	/*
	 * Make sure to accomodate the largest possible
	 * size of SA(if_lladdr)->sa_len.
	 */
	_CASSERT(sizeof (sdlbuf) == (SOCK_MAXADDRLEN + 1));

	if (interface == NULL || lladdr == NULL)
		return (EINVAL);

	ifa = interface->if_lladdr;
	IFA_LOCK_SPIN(ifa);
	bcopy(ifa->ifa_addr, &sdlbuf, SDL(ifa->ifa_addr)->sdl_len);
	IFA_UNLOCK(ifa);

	bytes = dlil_ifaddr_bytes(SDL(&sdlbuf), &bytes_len, credp);
	if (bytes_len != lladdr_len) {
		bzero(lladdr, lladdr_len);
		error = EMSGSIZE;
	} else {
		bcopy(bytes, lladdr, bytes_len);
	}

	return (error);
}