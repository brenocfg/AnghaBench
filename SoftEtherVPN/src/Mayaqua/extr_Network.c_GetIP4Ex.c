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
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int GetIP4Ex6Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int*) ; 

bool GetIP4Ex(IP *ip, char *hostname, UINT timeout, bool *cancel)
{
	return GetIP4Ex6Ex(ip, hostname, timeout, false, cancel);
}