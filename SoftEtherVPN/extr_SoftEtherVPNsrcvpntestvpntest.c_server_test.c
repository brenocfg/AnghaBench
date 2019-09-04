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

/* Variables and functions */
 int /*<<< orphan*/  GetLine (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Print (char*) ; 
 int /*<<< orphan*/  StFree () ; 
 int /*<<< orphan*/  StInit () ; 
 int /*<<< orphan*/  StStartServer (int) ; 
 int /*<<< orphan*/  StStopServer () ; 

void server_test(UINT num, char **arg)
{
	Print("VPN Server Test. Press Enter key to stop the VPN Server .\n");

	StInit();

	StStartServer(false);

	GetLine(NULL, 0);

	StStopServer();

	StFree();
}