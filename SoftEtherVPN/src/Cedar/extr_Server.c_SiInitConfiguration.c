#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct TYPE_16__ {int Bridge; } ;
struct TYPE_15__ {int AutoSaveConfigSpan; int BackupConfigOnlyWhenModified; int NoLinuxArpFilter; int AutoSaveConfigSpanSaved; scalar_t__ ServerType; int /*<<< orphan*/  SaveThread; int /*<<< orphan*/  SaveHaltEvent; TYPE_6__* Cedar; int /*<<< orphan*/  EnableVpnAzure; int /*<<< orphan*/  AzureClient; int /*<<< orphan*/ * DDnsClient; scalar_t__ DisableDosProtection; int /*<<< orphan*/  DontBackupConfig; TYPE_1__* CfgRw; int /*<<< orphan*/  OpenVpnServerUdp; int /*<<< orphan*/  IPsecServer; } ;
struct TYPE_14__ {int /*<<< orphan*/  DontBackup; } ;
struct TYPE_13__ {scalar_t__ OsType; } ;
typedef  TYPE_2__ SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  AcSetEnable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DisableDosProtect () ; 
 int /*<<< orphan*/  EnableDosProtect () ; 
 TYPE_12__* GetOsInfo () ; 
 int /*<<< orphan*/  InitEth () ; 
 int /*<<< orphan*/  MEM_FIFO_REALLOC_MEM_SIZE ; 
 int MIN (int,int /*<<< orphan*/ ) ; 
 scalar_t__ MsIsUserMode () ; 
 int /*<<< orphan*/  NewAzureClient (TYPE_6__*,TYPE_2__*) ; 
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/  NewIPsecServer (TYPE_6__*) ; 
 int /*<<< orphan*/  NewOpenVpnServerUdp (TYPE_6__*) ; 
 int /*<<< orphan*/  NewThread (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ OSTYPE_LINUX ; 
 int SERVER_FILE_SAVE_INTERVAL_DEFAULT ; 
 int /*<<< orphan*/  SERVER_FILE_SAVE_INTERVAL_USERMODE ; 
 scalar_t__ SERVER_TYPE_STANDALONE ; 
 int /*<<< orphan*/  SLog (TYPE_6__*,char*,...) ; 
 int /*<<< orphan*/  SetFifoCurrentReallocMemSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLinuxArpFilter () ; 
 int SiLoadConfigurationFile (TYPE_2__*) ; 
 int /*<<< orphan*/  SiLoadInitialConfiguration (TYPE_2__*) ; 
 int /*<<< orphan*/  SiSaverThread ; 
 int server_reset_setting ; 

void SiInitConfiguration(SERVER *s)
{
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	s->AutoSaveConfigSpan = SERVER_FILE_SAVE_INTERVAL_DEFAULT;
	s->BackupConfigOnlyWhenModified = true;

	// IPsec server
	if (s->Cedar->Bridge == false)
	{
		s->IPsecServer = NewIPsecServer(s->Cedar);
	}

	// OpenVPN server (UDP)
	if (s->Cedar->Bridge == false)
	{
		s->OpenVpnServerUdp = NewOpenVpnServerUdp(s->Cedar);
	}

	SLog(s->Cedar, "LS_LOAD_CONFIG_1");
	if (SiLoadConfigurationFile(s) == false)
	{
		// Ethernet initialization
		InitEth();

		SLog(s->Cedar, "LS_LOAD_CONFIG_3");
		SiLoadInitialConfiguration(s);

		SetFifoCurrentReallocMemSize(MEM_FIFO_REALLOC_MEM_SIZE);

		server_reset_setting = false;
	}
	else
	{
		SLog(s->Cedar, "LS_LOAD_CONFIG_2");
	}

	s->CfgRw->DontBackup = s->DontBackupConfig;

	// The arp_filter in Linux
	if (GetOsInfo()->OsType == OSTYPE_LINUX)
	{
		if (s->NoLinuxArpFilter == false)
		{
			SetLinuxArpFilter();
		}
	}

	if (s->DisableDosProtection)
	{
		DisableDosProtect();
	}
	else
	{
		EnableDosProtect();
	}

	s->AutoSaveConfigSpanSaved = s->AutoSaveConfigSpan;

	// Create a VPN Azure client
	if (s->DDnsClient != NULL && s->Cedar->Bridge == false && s->ServerType == SERVER_TYPE_STANDALONE)
	{
		s->AzureClient = NewAzureClient(s->Cedar, s);

		AcSetEnable(s->AzureClient, s->EnableVpnAzure);
	}

	// Reduce the storage interval in the case of user mode
#ifdef	OS_WIN32
	if (MsIsUserMode())
	{
		s->AutoSaveConfigSpan = MIN(s->AutoSaveConfigSpan, SERVER_FILE_SAVE_INTERVAL_USERMODE);
	}
#endif	//OS_WIN32

	// Create a saving thread
	SLog(s->Cedar, "LS_INIT_SAVE_THREAD", s->AutoSaveConfigSpan / 1000);
	s->SaveHaltEvent = NewEvent();
	s->SaveThread = NewThread(SiSaverThread, s);
}