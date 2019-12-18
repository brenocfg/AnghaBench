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

/* Variables and functions */
 void* LoadMessageA (int /*<<< orphan*/ ) ; 
 void* LoadMessageW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MESSAGE_OFFSET_EN ; 
 int /*<<< orphan*/  MESSAGE_OFFSET_JP ; 
 int /*<<< orphan*/  _e_msgAppTitle ; 
 int /*<<< orphan*/  _e_msgBadInfFile ; 
 int /*<<< orphan*/  _e_msgButtonForVpnClient ; 
 int /*<<< orphan*/  _e_msgButtonForVpnServer ; 
 int /*<<< orphan*/  _e_msgDownloading ; 
 int /*<<< orphan*/  _e_msgInfDownload ; 
 int /*<<< orphan*/  _e_msgInfDownloadFailed ; 
 int /*<<< orphan*/  _e_msgNoParam ; 
 int /*<<< orphan*/  _e_msgNotSupported ; 
 int /*<<< orphan*/  _e_msgProcessCreated ; 
 int /*<<< orphan*/  _e_msgProcessCreatedForVpnServer ; 
 int /*<<< orphan*/  _e_msgProcessCreating ; 
 int /*<<< orphan*/  _e_msgProcessFailed ; 
 int /*<<< orphan*/  _e_msgStartTextForVpnClient ; 
 int /*<<< orphan*/  _e_msgStartTextForVpnServer ; 
 int /*<<< orphan*/  _e_msgUserCancel ; 
 int /*<<< orphan*/  _e_msgWarning ; 
 int /*<<< orphan*/  _e_msgWarningTitle ; 
 int /*<<< orphan*/  _e_msgWriteFailed ; 
 int /*<<< orphan*/  currentPage ; 
 void* msgAppTitle ; 
 void* msgBadInfFile ; 
 void* msgButtonForVpnClient ; 
 void* msgButtonForVpnServer ; 
 void* msgDownloading ; 
 void* msgInfDownload ; 
 void* msgInfDownloadFailed ; 
 void* msgNoParam ; 
 void* msgNotSupported ; 
 void* msgProcessCreated ; 
 void* msgProcessCreatedForVpnServer ; 
 void* msgProcessCreating ; 
 void* msgProcessFailed ; 
 void* msgStartTextForVpnClient ; 
 void* msgStartTextForVpnServer ; 
 void* msgUserCancel ; 
 void* msgWarning ; 
 void* msgWarningTitle ; 
 void* msgWriteFailed ; 
 scalar_t__ stricmp (char*,char*) ; 

int LoadTables(char *pTag){
	if( stricmp(pTag,"JP")==0 || stricmp(pTag,"JA")==0){
		currentPage=MESSAGE_OFFSET_JP;
		
	}else if( stricmp(pTag,"EN")==0)
	{
		currentPage=MESSAGE_OFFSET_EN;
	}
//		currentPage=MESSAGE_OFFSET_EN;

	msgAppTitle=LoadMessageW(_e_msgAppTitle);
	msgNotSupported=LoadMessageA(_e_msgNotSupported);
	msgInfDownload=LoadMessageW(_e_msgInfDownload);
	msgInfDownloadFailed=LoadMessageW(_e_msgInfDownloadFailed);
	msgBadInfFile=LoadMessageW(_e_msgBadInfFile);
	msgWriteFailed=LoadMessageW(_e_msgWriteFailed);
	msgDownloading=LoadMessageW(_e_msgDownloading);
	msgProcessFailed=LoadMessageW(_e_msgProcessFailed);
	msgProcessCreating=LoadMessageW(_e_msgProcessCreating);
	msgProcessCreated=LoadMessageW(_e_msgProcessCreated);
	msgWarning=LoadMessageW(_e_msgWarning);
	msgWarningTitle=LoadMessageW(_e_msgWarningTitle);
	msgUserCancel=LoadMessageW(_e_msgUserCancel);
	msgStartTextForVpnServer=LoadMessageW(_e_msgStartTextForVpnServer);
	msgButtonForVpnServer=LoadMessageW(_e_msgButtonForVpnServer);
	msgProcessCreatedForVpnServer=LoadMessageW(_e_msgProcessCreatedForVpnServer);
	msgNoParam=LoadMessageA(_e_msgNoParam);
	msgStartTextForVpnClient=LoadMessageW(_e_msgStartTextForVpnClient);
	msgButtonForVpnClient=LoadMessageW(_e_msgButtonForVpnClient);
	return 0;

}