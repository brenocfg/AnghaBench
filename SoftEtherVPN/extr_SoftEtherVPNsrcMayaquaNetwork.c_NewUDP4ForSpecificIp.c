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
typedef  int /*<<< orphan*/  local_ip ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  GetBestLocalIpForTarget (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IsIP4 (int /*<<< orphan*/ *) ; 
 scalar_t__ IsZeroIP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewUDP4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

SOCK *NewUDP4ForSpecificIp(IP *target_ip, UINT port)
{
	SOCK *s;
	IP local_ip;
	// Validate arguments
	if (target_ip == NULL || IsZeroIP(target_ip) || IsIP4(target_ip) == false)
	{
		target_ip = NULL;
	}

	Zero(&local_ip, sizeof(local_ip));
	GetBestLocalIpForTarget(&local_ip, target_ip);

	s = NewUDP4(port, &local_ip);

	if (s == NULL)
	{
		s = NewUDP4(port, NULL);
	}

	return s;
}