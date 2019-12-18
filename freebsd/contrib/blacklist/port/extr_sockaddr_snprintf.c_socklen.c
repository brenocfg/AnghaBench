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
typedef  int u_int ;
struct sockaddr_un {int dummy; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr_dl {int dummy; } ;
struct sockaddr_at {int dummy; } ;
typedef  int socklen_t ;

/* Variables and functions */
#define  AF_APPLETALK 132 
#define  AF_INET 131 
#define  AF_INET6 130 
#define  AF_LINK 129 
#define  AF_LOCAL 128 

__attribute__((used)) static socklen_t
socklen(u_int af)
{
	switch (af) {
	case AF_INET:
		return sizeof(struct sockaddr_in);
	case AF_INET6:
		return sizeof(struct sockaddr_in6);
	case AF_LOCAL:
		return sizeof(struct sockaddr_un);
#ifdef HAVE_NET_IF_DL_H
	case AF_LINK:
		return sizeof(struct sockaddr_dl);
#endif
#ifdef HAVE_NETATALK_AT_H
	case AF_APPLETALK:
		return sizeof(struct sockaddr_at);
#endif
	default:
		return sizeof(struct sockaddr_storage);
	}
}