#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int h; int /*<<< orphan*/  pUnused; } ;
typedef  TYPE_1__ unixFile ;
typedef  int /*<<< orphan*/  sqlite3_file ;

/* Variables and functions */
 int /*<<< orphan*/  OSTRACE (char*) ; 
 int /*<<< orphan*/  OpenCounter (int) ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  robust_close (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unixUnmapfile (TYPE_1__*) ; 

__attribute__((used)) static int closeUnixFile(sqlite3_file *id){
  unixFile *pFile = (unixFile*)id;
  unixUnmapfile(pFile);
  if( pFile->h>=0 ){
    robust_close(pFile, pFile->h, __LINE__);
    pFile->h = -1;
  }
#if OS_VXWORKS
  if( pFile->pId ){
    if( pFile->ctrlFlags & UNIXFILE_DELETE ){
      osUnlink(pFile->pId->zCanonicalName);
    }
    vxworksReleaseFileId(pFile->pId);
    pFile->pId = 0;
  }
#endif
  OSTRACE(("CLOSE   %-3d\n", pFile->h));
  OpenCounter(-1);
  sqlite3_free(pFile->pUnused);
  memset(pFile, 0, sizeof(unixFile));
  return SQLITE_OK;
}