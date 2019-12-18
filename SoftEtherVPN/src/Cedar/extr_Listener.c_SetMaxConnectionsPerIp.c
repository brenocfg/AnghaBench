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
typedef  scalar_t__ UINT ;

/* Variables and functions */
 scalar_t__ DEFAULT_MAX_CONNECTIONS_PER_IP ; 
 int /*<<< orphan*/  MAX (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN_MAX_CONNECTIONS_PER_IP ; 
 int /*<<< orphan*/  max_connections_per_ip ; 

void SetMaxConnectionsPerIp(UINT num)
{
	if (num == 0)
	{
		num = DEFAULT_MAX_CONNECTIONS_PER_IP;
	}
	max_connections_per_ip = MAX(num, MIN_MAX_CONNECTIONS_PER_IP);
}