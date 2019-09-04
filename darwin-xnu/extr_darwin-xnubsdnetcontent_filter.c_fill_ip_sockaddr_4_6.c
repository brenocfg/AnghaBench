#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_len; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
union sockaddr_in_4_6 {struct sockaddr_in sin; } ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 

__attribute__((used)) static void
fill_ip_sockaddr_4_6(union sockaddr_in_4_6 *sin46,
	struct in_addr ip, u_int16_t port)
{
	struct sockaddr_in *sin = &sin46->sin;

	sin->sin_family = AF_INET;
	sin->sin_len = sizeof(*sin);
	sin->sin_port = port;
	sin->sin_addr.s_addr = ip.s_addr;
}