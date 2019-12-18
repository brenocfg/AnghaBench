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
struct sockaddr {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 size_t rpc_ntop4 (struct sockaddr const*,char*,size_t const) ; 
 size_t rpc_ntop6 (struct sockaddr const*,char*,size_t const) ; 

size_t rpc_ntop(const struct sockaddr *sap, char *buf, const size_t buflen)
{
	switch (sap->sa_family) {
	case AF_INET:
		return rpc_ntop4(sap, buf, buflen);
	case AF_INET6:
		return rpc_ntop6(sap, buf, buflen);
	}

	return 0;
}