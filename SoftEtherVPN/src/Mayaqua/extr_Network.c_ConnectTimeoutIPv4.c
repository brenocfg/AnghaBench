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
struct sockaddr_in {int /*<<< orphan*/  s_addr; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int dummy; } ;
struct in_addr {int /*<<< orphan*/  s_addr; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; int /*<<< orphan*/  sin_port; } ;
typedef  int /*<<< orphan*/  sockaddr4 ;
typedef  int /*<<< orphan*/  addr4 ;
typedef  int /*<<< orphan*/  USHORT ;
typedef  scalar_t__ UINT ;
typedef  scalar_t__ SOCKET ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  IPToInAddr (struct sockaddr_in*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  Zero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 scalar_t__ connect_timeout (scalar_t__,struct sockaddr*,int,scalar_t__,int*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

SOCKET ConnectTimeoutIPv4(IP *ip, UINT port, UINT timeout, bool *cancel_flag)
{
	SOCKET s;
	struct sockaddr_in sockaddr4;
	struct in_addr addr4;

	Zero(&sockaddr4, sizeof(sockaddr4));
	Zero(&addr4, sizeof(addr4));

	// Generate a sockaddr_in
	IPToInAddr(&addr4, ip);
	sockaddr4.sin_port = htons((USHORT)port);
	sockaddr4.sin_family = AF_INET;
	sockaddr4.sin_addr.s_addr = addr4.s_addr;

	// Socket creation
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s != INVALID_SOCKET)
	{
		// Connection
		if (connect_timeout(s, (struct sockaddr *)&sockaddr4, sizeof(struct sockaddr_in), timeout, cancel_flag) != 0)
		{
			// Connection failure
			closesocket(s);
			s = INVALID_SOCKET;
		}
	}

	return s;
}