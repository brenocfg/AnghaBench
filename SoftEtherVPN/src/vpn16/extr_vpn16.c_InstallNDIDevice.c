#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* szClassName; int Flags; int /*<<< orphan*/  szRegSubkey; int /*<<< orphan*/ * hRegKey; scalar_t__ lpCompatDrvList; scalar_t__ lpSelectedDriver; int /*<<< orphan*/  atDriverPath; } ;
typedef  scalar_t__ RETERR ;
typedef  TYPE_1__* LPDEVICE_INFO ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  DIF_INSTALLDEVICE ; 
 int /*<<< orphan*/  DIREG_DEV ; 
 int DI_ENUMSINGLEINF ; 
 int DI_NOFILECOPY ; 
 int DI_NOVCP ; 
 int DI_QUIETINSTALL ; 
 scalar_t__ DiBuildCompatDrvList (TYPE_1__*) ; 
 scalar_t__ DiCallClassInstaller (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ DiCreateDevRegKey (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ DiCreateDeviceInfo (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DiDeleteDevRegKey (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DiDestroyDeviceInfoList (TYPE_1__*) ; 
 scalar_t__ DiSelectDevice (TYPE_1__*) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GlobalAddAtom (char const*) ; 
 void* HKEY_LOCAL_MACHINE ; 
 scalar_t__ OK ; 
 char* REGSTR_VAL_COMPATIBLEIDS ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  SURegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ SURegSetValueEx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  lstrcat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lstrcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ lstrlen (char const*) ; 

RETERR InstallNDIDevice(const char* szClass,
						const char* szDeviceID, 
						const char* szDriverPath,
						const char* szRegPath)
{
	char *szClassNetProtocol    = "NetTrans"; 
	char *szClassNet            = "Net";
	char *szClassNetClient      = "NetClient";
	char *szClassNetService		= "NetService";
	char *szNull                = "";
	char *szClassNetInfFileName        = "Net.inf";
	char *szClassNetTransInfFileName   = "Nettrans.inf";
	char *szClassNetClientInfFileName  = "Netcli.inf";
	char *szClassNetServiceInfFileName = "Netservr.inf";
	char *szRegKeyNdi           = "Ndi";
	char *szRegKeyBindings      = "Bindings";
	char *szRegValDeviceID      = "DeviceID";
	char *szRegValDriverDesc	= "DriverDesc";
	char *szRegValCompatibleIDs = REGSTR_VAL_COMPATIBLEIDS;
	char *szRegPathNetwork      = "Enum\\Network\\";
	char *szRegPathFilter       = "Enum\\Filter\\";
	char *szRegPathTemp         = "\\Temp";
	char *szVServer				= "VSERVER";
	LPDEVICE_INFO lpdi = NULL;
	RETERR	      err  = OK;

	err = DiCreateDeviceInfo( &lpdi, NULL, 0, NULL, NULL, szClass, NULL );
	
	if (err == OK)
	{
		HKEY hKeyTmp;
		
		lpdi->hRegKey = HKEY_LOCAL_MACHINE;
		lstrcpy( lpdi->szRegSubkey, szRegPathNetwork );
		lstrcat( lpdi->szRegSubkey, lpdi->szClassName );
		lstrcat( lpdi->szRegSubkey, szRegPathTemp );

		err = DiCreateDevRegKey( lpdi, &hKeyTmp, NULL, NULL, DIREG_DEV );

		if (err == OK)
		{
			if (SURegSetValueEx(hKeyTmp, 
			                      szRegValCompatibleIDs, 
			                      0, 
			                      REG_SZ, 
			                      (unsigned char *) szDeviceID,
			                      lstrlen( szDeviceID ) + 1 ) == ERROR_SUCCESS )
			{
            if ( szDriverPath )
            {
               if ( lpdi->atDriverPath = GlobalAddAtom( szDriverPath ) )
                  lpdi->Flags |= DI_ENUMSINGLEINF;
				}

				err = DiBuildCompatDrvList( lpdi );
				
				SURegCloseKey( hKeyTmp );
				
				DiDeleteDevRegKey( lpdi, DIREG_DEV );
				lpdi->hRegKey = NULL;
				lstrcpy( lpdi->szRegSubkey, szNull );

				if ( err || !lpdi->lpCompatDrvList )
				{
					err = DiSelectDevice( lpdi );		
				}
				else
				{
					lpdi->lpSelectedDriver = lpdi->lpCompatDrvList;
				}
				
				if ( err == OK )
				{
					if ( szRegPath )
					{
						lpdi->hRegKey = HKEY_LOCAL_MACHINE;
						lstrcpy( lpdi->szRegSubkey, szRegPath );
						
						DiCreateDevRegKey( lpdi, &hKeyTmp, NULL, NULL, DIREG_DEV );
					}

					lpdi->Flags |= DI_NOVCP | DI_NOFILECOPY | DI_QUIETINSTALL;
               err = DiCallClassInstaller( DIF_INSTALLDEVICE, lpdi );
				}
            else
            {
               DiDestroyDeviceInfoList( lpdi );
            }
			}
			else
			{
				DiDeleteDevRegKey( lpdi, DIREG_DEV );
            DiDestroyDeviceInfoList( lpdi );
			}
		}
      else
      {
         DiDestroyDeviceInfoList( lpdi );
      }
	}

	return err;		                 
}