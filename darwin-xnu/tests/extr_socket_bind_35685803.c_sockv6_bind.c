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
struct sockaddr_in6 {int sin6_len; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sin6 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int bind (int,struct sockaddr const*,int) ; 
 int /*<<< orphan*/  htons (int) ; 

__attribute__((used)) static int
sockv6_bind(int s, int port)
{
	struct sockaddr_in6		sin6 = {
		.sin6_len = sizeof(sin6),
		.sin6_family = AF_INET6,
	};

	sin6.sin6_port = htons(port);
	return (bind(s, (const struct sockaddr *)&sin6, sizeof(sin6)));
}