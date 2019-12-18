#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  OsType; } ;
struct TYPE_8__ {int AllowRemoteConfig; int UseKeepConnect; int /*<<< orphan*/  KeepConnectInterval; int /*<<< orphan*/  KeepConnectProtocol; int /*<<< orphan*/  KeepConnectPort; int /*<<< orphan*/  KeepConnectHost; } ;
struct TYPE_9__ {int /*<<< orphan*/  Logger; int /*<<< orphan*/  Eraser; TYPE_1__ Config; int /*<<< orphan*/  EncryptedPassword; void* UnixVLanList; void* AccountList; } ;
typedef  TYPE_2__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_DEFAULT_KEEPALIVE_HOST ; 
 int /*<<< orphan*/  CLIENT_DEFAULT_KEEPALIVE_INTERVAL ; 
 int /*<<< orphan*/  CLIENT_DEFAULT_KEEPALIVE_PORT ; 
 int /*<<< orphan*/  CLog (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  CONNECTION_UDP ; 
 int /*<<< orphan*/  CiCompareAccount ; 
 int /*<<< orphan*/  CiCompareUnixVLan ; 
 int CiLoadConfigurationFile (TYPE_2__*) ; 
 int /*<<< orphan*/  CiSetVLanToDefault (TYPE_2__*) ; 
 TYPE_3__* GetOsInfo () ; 
 int /*<<< orphan*/  NewEraser (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* NewList (int /*<<< orphan*/ ) ; 
 scalar_t__ OS_IS_UNIX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sha0 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnixVLanInit () ; 

void CiInitConfiguration(CLIENT *c)
{
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

#ifdef	OS_UNIX
	// Initialize the VLAN
	UnixVLanInit();
#endif	 // OS_UNIX

	// Account list
	c->AccountList = NewList(CiCompareAccount);

	// Unix version VLAN list
	if (OS_IS_UNIX(GetOsInfo()->OsType))
	{
		c->UnixVLanList = NewList(CiCompareUnixVLan);
	}

	// Read the configuration file
	CLog(c, "LC_LOAD_CONFIG_1");
	if (CiLoadConfigurationFile(c) == false)
	{
		CLog(c, "LC_LOAD_CONFIG_3");
		// Do the initial setup because the configuration file does not exist
		// Clear the password
		Sha0(c->EncryptedPassword, "", 0);
		// Initialize the client configuration
		// Disable remote management
		c->Config.AllowRemoteConfig = false;
		StrCpy(c->Config.KeepConnectHost, sizeof(c->Config.KeepConnectHost), CLIENT_DEFAULT_KEEPALIVE_HOST);
		c->Config.KeepConnectPort = CLIENT_DEFAULT_KEEPALIVE_PORT;
		c->Config.KeepConnectProtocol = CONNECTION_UDP;
		c->Config.KeepConnectInterval = CLIENT_DEFAULT_KEEPALIVE_INTERVAL;
		c->Config.UseKeepConnect = false;	// Don't use the connection maintenance function by default in the Client
		// Eraser
		c->Eraser = NewEraser(c->Logger, 0);
	}
	else
	{
		CLog(c, "LC_LOAD_CONFIG_2");
	}

	// Appropriate setting for virtual LAN card
	CiSetVLanToDefault(c);
}