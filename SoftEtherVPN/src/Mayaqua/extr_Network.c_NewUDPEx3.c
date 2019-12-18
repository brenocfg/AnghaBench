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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 scalar_t__ IsIP4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewUDPEx2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

SOCK *NewUDPEx3(UINT port, IP *ip)
{
	// Validate arguments
	if (ip == NULL)
	{
		return NewUDPEx2(port, false, NULL);
	}

	if (IsIP4(ip))
	{
		return NewUDPEx2(port, false, ip);
	}
	else
	{
		return NewUDPEx2(port, true, ip);
	}
}