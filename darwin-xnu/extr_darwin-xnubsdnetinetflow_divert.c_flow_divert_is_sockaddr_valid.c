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
struct sockaddr_in {int dummy; } ;
struct sockaddr {int sa_family; int sa_len; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
#define  AF_INET 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static boolean_t
flow_divert_is_sockaddr_valid(struct sockaddr *addr)
{
	switch(addr->sa_family)
	{
		case AF_INET:
			if (addr->sa_len != sizeof(struct sockaddr_in)) {
				return FALSE;
			}
			break;
#if INET6
		case AF_INET6:
			if (addr->sa_len != sizeof(struct sockaddr_in6)) {
				return FALSE;
			}
			break;
#endif	/* INET6 */
		default:
			return FALSE;
	}
	return TRUE;
}