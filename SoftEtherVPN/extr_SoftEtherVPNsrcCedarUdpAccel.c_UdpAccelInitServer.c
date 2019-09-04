#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {scalar_t__ IsIPv6; int Inited; int /*<<< orphan*/  Now; int /*<<< orphan*/  YourPort; int /*<<< orphan*/  YourIp2; int /*<<< orphan*/  YourIp; int /*<<< orphan*/ * YourKey; int /*<<< orphan*/  YourCookie; int /*<<< orphan*/  MyCookie; } ;
typedef  TYPE_1__ UDP_ACCEL ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Debug (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPToStr (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ IsIP6 (int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  Tick64 () ; 
 int UDP_ACCELERATION_COMMON_KEY_SIZE ; 

bool UdpAccelInitServer(UDP_ACCEL *a, UCHAR *client_key, IP *client_ip, UINT client_port, IP *client_ip_2)
{
	char tmp[MAX_SIZE];
	// Validate arguments
	if (a == NULL || client_key == NULL)
	{
		return false;
	}

	IPToStr(tmp, sizeof(tmp), client_ip);
	Debug("UdpAccelInitServer: client_ip=%s, client_port=%u, server_cookie=%u, client_cookie=%u\n", tmp, client_port,
		a->MyCookie, a->YourCookie);

	if (IsIP6(client_ip) != a->IsIPv6)
	{
		return false;
	}

	Copy(a->YourKey, client_key, UDP_ACCELERATION_COMMON_KEY_SIZE);

	Copy(&a->YourIp, client_ip, sizeof(IP));
	Copy(&a->YourIp2, client_ip_2, sizeof(IP));
	a->YourPort = client_port;

	a->Now = Tick64();

	a->Inited = true;

	return true;
}