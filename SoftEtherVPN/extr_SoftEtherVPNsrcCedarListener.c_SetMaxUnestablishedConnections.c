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
 scalar_t__ DEFAULT_MAX_UNESTABLISHED_CONNECTIONS ; 
 int /*<<< orphan*/  MAX (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_connections_per_ip ; 
 int /*<<< orphan*/  max_unestablished_connections ; 

void SetMaxUnestablishedConnections(UINT num)
{
	if (num == 0)
	{
		num = DEFAULT_MAX_UNESTABLISHED_CONNECTIONS;
	}

	max_unestablished_connections = MAX(num, max_connections_per_ip);
}