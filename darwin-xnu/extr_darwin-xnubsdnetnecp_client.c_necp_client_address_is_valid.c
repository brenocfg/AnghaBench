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
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {scalar_t__ sa_family; int sa_len; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int FALSE ; 

__attribute__((used)) static inline bool
necp_client_address_is_valid(struct sockaddr *address)
{
	if (address->sa_family == AF_INET) {
		return (address->sa_len == sizeof(struct sockaddr_in));
	} else if (address->sa_family == AF_INET6) {
		return (address->sa_len == sizeof(struct sockaddr_in6));
	} else {
		return (FALSE);
	}
}