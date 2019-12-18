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
struct sockaddr_in6 {void* sin6_port; } ;
struct sockaddr_in {void* sin_port; } ;
struct sockaddr {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 void* htons (unsigned short const) ; 

int
cifs_set_port(struct sockaddr *addr, const unsigned short int port)
{
	switch (addr->sa_family) {
	case AF_INET:
		((struct sockaddr_in *)addr)->sin_port = htons(port);
		break;
	case AF_INET6:
		((struct sockaddr_in6 *)addr)->sin6_port = htons(port);
		break;
	default:
		return 0;
	}
	return 1;
}