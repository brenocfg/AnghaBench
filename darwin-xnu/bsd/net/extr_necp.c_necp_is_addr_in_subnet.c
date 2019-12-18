#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
struct sockaddr {int sa_family; scalar_t__ sa_len; } ;
struct TYPE_4__ {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; } ;
struct TYPE_3__ {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_port; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int FALSE ; 
 int necp_buffer_compare_with_bit_prefix (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* satosin (struct sockaddr*) ; 
 TYPE_1__* satosin6 (struct sockaddr*) ; 

__attribute__((used)) static bool
necp_is_addr_in_subnet(struct sockaddr *addr, struct sockaddr *subnet_addr, u_int8_t subnet_prefix)
{
	if (addr == NULL || subnet_addr == NULL) {
		return (FALSE);
	}

	if (addr->sa_family != subnet_addr->sa_family || addr->sa_len != subnet_addr->sa_len) {
		return (FALSE);
	}

	switch (addr->sa_family) {
		case AF_INET: {
			if (satosin(subnet_addr)->sin_port != 0 &&
				satosin(addr)->sin_port != satosin(subnet_addr)->sin_port) {
				return (FALSE);
			}
			return (necp_buffer_compare_with_bit_prefix((u_int8_t *)&satosin(addr)->sin_addr, (u_int8_t *)&satosin(subnet_addr)->sin_addr, subnet_prefix));
		}
		case AF_INET6: {
			if (satosin6(subnet_addr)->sin6_port != 0 &&
				satosin6(addr)->sin6_port != satosin6(subnet_addr)->sin6_port) {
				return (FALSE);
			}
			if (satosin6(addr)->sin6_scope_id &&
				satosin6(subnet_addr)->sin6_scope_id &&
				satosin6(addr)->sin6_scope_id != satosin6(subnet_addr)->sin6_scope_id) {
				return (FALSE);
			}
			return (necp_buffer_compare_with_bit_prefix((u_int8_t *)&satosin6(addr)->sin6_addr, (u_int8_t *)&satosin6(subnet_addr)->sin6_addr, subnet_prefix));
		}
		default: {
			return (FALSE);
		}
	}

	return (FALSE);
}