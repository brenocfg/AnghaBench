#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qboolean ;
typedef  scalar_t__ fileHandle_t ;
typedef  int /*<<< orphan*/  descPath ;
struct TYPE_6__ {char* string; } ;
struct TYPE_5__ {char* string; } ;
struct TYPE_4__ {char* string; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memset (char*,int /*<<< orphan*/ ,int) ; 
 char* FS_BuildOSPath (char*,char*,char*) ; 
 int /*<<< orphan*/  FS_FCloseFile (scalar_t__) ; 
 int /*<<< orphan*/ * FS_FileForHandle (scalar_t__) ; 
 int FS_SV_FOpenFileRead (char*,scalar_t__*) ; 
 int MAX_OSPATH ; 
 scalar_t__ Q_stricmp (char*,char*) ; 
 scalar_t__ Q_stricmpn (char*,char*,int) ; 
 char** Sys_ConcatenateFileLists (char**,char**,char**) ; 
 int Sys_CountFileList (char**) ; 
 int /*<<< orphan*/  Sys_FreeFileList (char**) ; 
 char** Sys_ListFiles (char*,char*,int /*<<< orphan*/ *,int*,scalar_t__) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 TYPE_3__* fs_basepath ; 
 TYPE_2__* fs_cdpath ; 
 TYPE_1__* fs_homepath ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

int	FS_GetModList( char *listbuf, int bufsize ) {
  int		nMods, i, j, nTotal, nLen, nPaks, nPotential, nDescLen;
  char **pFiles = NULL;
  char **pPaks = NULL;
  char *name, *path;
  char descPath[MAX_OSPATH];
  fileHandle_t descHandle;

  int dummy;
  char **pFiles0 = NULL;
  char **pFiles1 = NULL;
  char **pFiles2 = NULL;
  qboolean bDrop = qfalse;

  *listbuf = 0;
  nMods = nPotential = nTotal = 0;

  pFiles0 = Sys_ListFiles( fs_homepath->string, NULL, NULL, &dummy, qtrue );
  pFiles1 = Sys_ListFiles( fs_basepath->string, NULL, NULL, &dummy, qtrue );
  pFiles2 = Sys_ListFiles( fs_cdpath->string, NULL, NULL, &dummy, qtrue );
  // we searched for mods in the three paths
  // it is likely that we have duplicate names now, which we will cleanup below
  pFiles = Sys_ConcatenateFileLists( pFiles0, pFiles1, pFiles2 );
  nPotential = Sys_CountFileList(pFiles);

  for ( i = 0 ; i < nPotential ; i++ ) {
    name = pFiles[i];
    // NOTE: cleaner would involve more changes
    // ignore duplicate mod directories
    if (i!=0) {
      bDrop = qfalse;
      for(j=0; j<i; j++)
      {
        if (Q_stricmp(pFiles[j],name)==0) {
          // this one can be dropped
          bDrop = qtrue;
          break;
        }
      }
    }
    if (bDrop) {
      continue;
    }
    // we drop "baseq3" "." and ".."
    if (Q_stricmp(name, "baseq3") && Q_stricmpn(name, ".", 1)) {
      // now we need to find some .pk3 files to validate the mod
      // NOTE TTimo: (actually I'm not sure why .. what if it's a mod under developement with no .pk3?)
      // we didn't keep the information when we merged the directory names, as to what OS Path it was found under
      //   so it could be in base path, cd path or home path
      //   we will try each three of them here (yes, it's a bit messy)
      path = FS_BuildOSPath( fs_basepath->string, name, "" );
      nPaks = 0;
      pPaks = Sys_ListFiles(path, ".pk3", NULL, &nPaks, qfalse); 
      Sys_FreeFileList( pPaks ); // we only use Sys_ListFiles to check wether .pk3 files are present

      /* Try on cd path */
      if( nPaks <= 0 ) {
        path = FS_BuildOSPath( fs_cdpath->string, name, "" );
        nPaks = 0;
        pPaks = Sys_ListFiles( path, ".pk3", NULL, &nPaks, qfalse );
        Sys_FreeFileList( pPaks );
      }

      /* try on home path */
      if ( nPaks <= 0 )
      {
        path = FS_BuildOSPath( fs_homepath->string, name, "" );
        nPaks = 0;
        pPaks = Sys_ListFiles( path, ".pk3", NULL, &nPaks, qfalse );
        Sys_FreeFileList( pPaks );
      }

      if (nPaks > 0) {
        nLen = strlen(name) + 1;
        // nLen is the length of the mod path
        // we need to see if there is a description available
        descPath[0] = '\0';
        strcpy(descPath, name);
        strcat(descPath, "/description.txt");
        nDescLen = FS_SV_FOpenFileRead( descPath, &descHandle );
        if ( nDescLen > 0 && descHandle) {
          FILE *file;
          file = FS_FileForHandle(descHandle);
          Com_Memset( descPath, 0, sizeof( descPath ) );
          nDescLen = fread(descPath, 1, 48, file);
          if (nDescLen >= 0) {
            descPath[nDescLen] = '\0';
          }
          FS_FCloseFile(descHandle);
        } else {
          strcpy(descPath, name);
        }
        nDescLen = strlen(descPath) + 1;

        if (nTotal + nLen + 1 + nDescLen + 1 < bufsize) {
          strcpy(listbuf, name);
          listbuf += nLen;
          strcpy(listbuf, descPath);
          listbuf += nDescLen;
          nTotal += nLen + nDescLen;
          nMods++;
        }
        else {
          break;
        }
      }
    }
  }
  Sys_FreeFileList( pFiles );

  return nMods;
}