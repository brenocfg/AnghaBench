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
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  IsIP6 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewDnsCacheEx (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void NewDnsCache(char *hostname, IP *ip)
{
	NewDnsCacheEx(hostname, ip, IsIP6(ip));
}