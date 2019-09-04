#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sockopt {size_t sopt_valsize; int /*<<< orphan*/  sopt_name; int /*<<< orphan*/  sopt_level; int /*<<< orphan*/  sopt_p; int /*<<< orphan*/  sopt_val; int /*<<< orphan*/  sopt_dir; } ;
typedef  TYPE_2__* socket_t ;
typedef  scalar_t__ errno_t ;
struct TYPE_9__ {TYPE_1__* so_proto; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pr_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_USER_ADDR_T (void*) ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_TCLASS ; 
 int /*<<< orphan*/  IP_TOS ; 
#define  PF_INET 129 
#define  PF_INET6 128 
 int SOCK_DOM (TYPE_2__*) ; 
 int /*<<< orphan*/  SOPT_GET ; 
 int /*<<< orphan*/  kernproc ; 
 int /*<<< orphan*/  socket_lock (TYPE_2__*,int) ; 
 int /*<<< orphan*/  socket_unlock (TYPE_2__*,int) ; 
 scalar_t__ sogetoptlock (TYPE_2__*,struct sockopt*,int /*<<< orphan*/ ) ; 

errno_t
sock_gettclassopt(socket_t sock, void *optval, size_t *optlen)
{
	errno_t error = 0;
	struct sockopt sopt;

	if (sock == NULL || optval == NULL || optlen == NULL)
		return (EINVAL);

	sopt.sopt_dir = SOPT_GET;
	sopt.sopt_val = CAST_USER_ADDR_T(optval);
	sopt.sopt_valsize = *optlen;
	sopt.sopt_p = kernproc;

	socket_lock(sock, 1);
	if (sock->so_proto == NULL || sock->so_proto->pr_domain == NULL) {
		socket_unlock(sock, 1);
		return (EINVAL);
	}

	switch (SOCK_DOM(sock)) {
	case PF_INET:
		sopt.sopt_level = IPPROTO_IP;
		sopt.sopt_name = IP_TOS;
		break;
	case PF_INET6:
		sopt.sopt_level = IPPROTO_IPV6;
		sopt.sopt_name = IPV6_TCLASS;
		break;
	default:
		socket_unlock(sock, 1);
		return (EINVAL);

	}
	error = sogetoptlock(sock, &sopt, 0);	/* already locked */
	socket_unlock(sock, 1);
	if (error == 0)
		*optlen = sopt.sopt_valsize;
	return (error);
}