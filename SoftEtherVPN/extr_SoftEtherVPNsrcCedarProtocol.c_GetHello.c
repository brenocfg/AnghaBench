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
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int PackGetData (int /*<<< orphan*/ *,char*,void*) ; 
 scalar_t__ PackGetDataSize (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int PackGetStr (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ SHA1_SIZE ; 

bool GetHello(PACK *p, void *random, UINT *ver, UINT *build, char *server_str, UINT server_str_size)
{
	// Validate arguments
	if (p == NULL || random == NULL || ver == NULL || server_str == NULL)
	{
		return false;
	}

	if (PackGetStr(p, "hello", server_str, server_str_size) == false)
	{
		return false;
	}
	*ver = PackGetInt(p, "version");
	*build = PackGetInt(p, "build");
	if (PackGetDataSize(p, "random") != SHA1_SIZE)
	{
		return false;
	}
	if (PackGetData(p, "random", random) == false)
	{
		return false;
	}

	return true;
}