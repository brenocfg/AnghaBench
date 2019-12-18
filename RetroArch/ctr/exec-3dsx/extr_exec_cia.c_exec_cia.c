#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_5__ {size_t argc; char* args; } ;
typedef  TYPE_1__ ciaParam ;
struct TYPE_6__ {int /*<<< orphan*/  titleID; int /*<<< orphan*/  version; } ;
typedef  int /*<<< orphan*/  Result ;
typedef  int /*<<< orphan*/  Handle ;
typedef  int /*<<< orphan*/  FS_Archive ;
typedef  TYPE_2__ AM_TitleEntry ;

/* Variables and functions */
 int /*<<< orphan*/  AM_GetCiaFileInfo (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APT_DoApplicationJump (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APT_PrepareToDoApplicationJump (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ARCHIVE_SDMC ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  FSFILE_Close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSUSER_CloseArchive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSUSER_OpenArchive (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSUSER_OpenFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_OPEN_READ ; 
 int /*<<< orphan*/  MEDIATYPE_SD ; 
 int /*<<< orphan*/  PATH_ASCII ; 
 int /*<<< orphan*/  PATH_EMPTY ; 
 scalar_t__ R_FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ R_SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amExit () ; 
 int /*<<< orphan*/  amInit () ; 
 int /*<<< orphan*/  argvHmac ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  errorAndQuit (char*) ; 
 int /*<<< orphan*/  fsExit () ; 
 int /*<<< orphan*/  fsInit () ; 
 int /*<<< orphan*/  fsMakePath (int /*<<< orphan*/ ,char const*) ; 
 int installCia (int /*<<< orphan*/ ) ; 
 int isCiaInstalled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

int exec_cia(const char* path, const char** args){
	struct stat sBuff;
	bool fileExists;
	bool inited;

	if(path == NULL || path[0] == '\0'){
		errno = EINVAL;
		return -1;
	}

	fileExists = stat(path, &sBuff) == 0;
	if(!fileExists){
		errno = ENOENT;
		return -1;
	}
	else if(S_ISDIR(sBuff.st_mode)){
		errno = EINVAL;;
		return -1;
	}

	inited = R_SUCCEEDED(amInit()) && R_SUCCEEDED(fsInit());
	if(inited){
		Result res;
		AM_TitleEntry ciaInfo;
		FS_Archive ciaArchive;
		Handle ciaFile;
		int ciaInstalled;
		ciaParam param;
		int argsLength;

		//open cia file
		res = FSUSER_OpenArchive(&ciaArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""));
		if(R_FAILED(res))
			errorAndQuit("Cant open SD FS archive.");

		res = FSUSER_OpenFile(&ciaFile, ciaArchive, fsMakePath(PATH_ASCII, path + 5/*skip "sdmc:"*/), FS_OPEN_READ, 0);
		if(R_FAILED(res))
			errorAndQuit("Cant open CIA file.");

		res = AM_GetCiaFileInfo(MEDIATYPE_SD, &ciaInfo, ciaFile);
		if(R_FAILED(res))
			errorAndQuit("Cant get CIA file info.");

		ciaInstalled = isCiaInstalled(ciaInfo.titleID, ciaInfo.version);
		if(ciaInstalled == -1){
			//error
			errorAndQuit("Could not read title id list.");
		}
		else if(ciaInstalled == 0){
			//not installed
			int error = installCia(ciaFile);
			if(error == -1)
				errorAndQuit("Cant install CIA.");
		}

		FSFILE_Close(ciaFile);
		FSUSER_CloseArchive(ciaArchive);

		param.argc = 0;
		argsLength = 0;
		char* argLocation = param.args;
		while(args[param.argc] != NULL){
			strcpy(argLocation, args[param.argc]);
			argLocation += strlen(args[param.argc]) + 1;
			argsLength += strlen(args[param.argc]) + 1;
			param.argc++;
		}

		res = APT_PrepareToDoApplicationJump(0, ciaInfo.titleID, 0x1);
		if(R_FAILED(res))
			errorAndQuit("CIA cant run, cant prepare.");

		res = APT_DoApplicationJump(&param, sizeof(param.argc) + argsLength, argvHmac);
		if(R_FAILED(res))
			errorAndQuit("CIA cant run, cant jump.");

		//wait for application jump, for some reason its not instant
		while(1);
	}

	//should never be reached
	amExit();
	fsExit();
	errno = ENOTSUP;
	return -1;
}