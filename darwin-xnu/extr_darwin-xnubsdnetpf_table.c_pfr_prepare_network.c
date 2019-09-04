#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int* s6_addr32; } ;
struct TYPE_8__ {int sin6_len; int sin6_family; TYPE_3__ sin6_addr; } ;
struct TYPE_5__ {void* s_addr; } ;
struct TYPE_6__ {int sin_len; int sin_family; TYPE_1__ sin_addr; } ;
union sockaddr_union {TYPE_4__ sin6; TYPE_2__ sin; } ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int /*<<< orphan*/  bzero (union sockaddr_union*,int) ; 
 void* htonl (int) ; 

__attribute__((used)) static void
pfr_prepare_network(union sockaddr_union *sa, int af, int net)
{
	int	i;

	bzero(sa, sizeof (*sa));
	if (af == AF_INET) {
		sa->sin.sin_len = sizeof (sa->sin);
		sa->sin.sin_family = AF_INET;
		sa->sin.sin_addr.s_addr = net ? htonl(-1 << (32-net)) : 0;
	} else if (af == AF_INET6) {
		sa->sin6.sin6_len = sizeof (sa->sin6);
		sa->sin6.sin6_family = AF_INET6;
		for (i = 0; i < 4; i++) {
			if (net <= 32) {
				sa->sin6.sin6_addr.s6_addr32[i] =
				    net ? htonl(-1 << (32-net)) : 0;
				break;
			}
			sa->sin6.sin6_addr.s6_addr32[i] = 0xFFFFFFFF;
			net -= 32;
		}
	}
}