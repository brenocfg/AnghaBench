#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int NoMoreSave; int Halt; int /*<<< orphan*/ * CfgRw; int /*<<< orphan*/ * AzureClient; int /*<<< orphan*/ * DDnsClient; int /*<<< orphan*/ * OpenVpnServerUdp; int /*<<< orphan*/ * IPsecServer; int /*<<< orphan*/ * SaveThread; int /*<<< orphan*/ * SaveHaltEvent; } ;
typedef  TYPE_1__ SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  FreeAzureClient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeCfgRw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeDDNSClient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeEth () ; 
 int /*<<< orphan*/  FreeIPsecServer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeOpenVpnServerUdp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiWriteConfigurationFile (TYPE_1__*) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void SiFreeConfiguration(SERVER *s)
{
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	// Write to the configuration file
	SiWriteConfigurationFile(s);

	// Terminate the configuration file saving thread
	s->NoMoreSave = true;
	s->Halt = true;
	Set(s->SaveHaltEvent);
	WaitThread(s->SaveThread, INFINITE);

	ReleaseEvent(s->SaveHaltEvent);
	ReleaseThread(s->SaveThread);

	s->SaveHaltEvent = NULL;
	s->SaveThread = NULL;


	// Stop the IPsec server
	if (s->IPsecServer != NULL)
	{
		FreeIPsecServer(s->IPsecServer);
		s->IPsecServer = NULL;
	}

	// Terminate the OpenVPN server
	if (s->OpenVpnServerUdp != NULL)
	{
		FreeOpenVpnServerUdp(s->OpenVpnServerUdp);
		s->OpenVpnServerUdp = NULL;
	}


	// Terminate the DDNS client
	if (s->DDnsClient != NULL)
	{
		FreeDDNSClient(s->DDnsClient);
		s->DDnsClient = NULL;
	}

	// Terminate the VPN Azure client
	if (s->AzureClient != NULL)
	{
		FreeAzureClient(s->AzureClient);
		s->AzureClient = NULL;
	}

	FreeCfgRw(s->CfgRw);
	s->CfgRw = NULL;

	// Release the Ethernet 
	FreeEth();
}