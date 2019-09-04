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
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct in_addr {int dummy; } ;
struct sockaddr_in {int sin_len; struct in_addr sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 

__attribute__((used)) static void
nstat_ip_to_sockaddr(
	const struct in_addr	*ip,
	u_int16_t				port,
	struct sockaddr_in		*sin,
	u_int32_t				maxlen)
{
	if (maxlen < sizeof(struct sockaddr_in))
		return;

	sin->sin_family = AF_INET;
	sin->sin_len = sizeof(*sin);
	sin->sin_port = port;
	sin->sin_addr = *ip;
}