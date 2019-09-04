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
struct sockaddr_in {int sin_len; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sin ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int bind (int,struct sockaddr const*,int) ; 
 int /*<<< orphan*/  htons (int) ; 

__attribute__((used)) static int
sock_bind(int s, int port)
{
	struct sockaddr_in	sin = {
		.sin_len = sizeof(sin),
		.sin_family = AF_INET,
	};

	sin.sin_port = htons(port);
	return (bind(s, (const struct sockaddr *)&sin, sizeof(sin)));
}