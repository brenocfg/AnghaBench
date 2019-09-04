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
struct stat {int st_mode; } ;
typedef  int mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_PATHNAME ; 
 int SQLITE_DEFAULT_FILE_PERMISSIONS ; 
 int SQLITE_IOERR_FSTAT ; 
 int SQLITE_OK ; 
 int SQLITE_OPEN_DELETEONCLOSE ; 
 int SQLITE_OPEN_MAIN_JOURNAL ; 
 int SQLITE_OPEN_WAL ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int sqlite3Strlen30 (char const*) ; 
 scalar_t__ stat (char*,struct stat*) ; 

__attribute__((used)) static int findCreateFileMode(
  const char *zPath,              /* Path of file (possibly) being created */
  int flags,                      /* Flags passed as 4th argument to xOpen() */
  mode_t *pMode                   /* OUT: Permissions to open file with */
){
  int rc = SQLITE_OK;             /* Return Code */
  *pMode = SQLITE_DEFAULT_FILE_PERMISSIONS;
  if( flags & (SQLITE_OPEN_WAL|SQLITE_OPEN_MAIN_JOURNAL) ){
    char zDb[MAX_PATHNAME+1];     /* Database file path */
    int nDb;                      /* Number of valid bytes in zDb */
    struct stat sStat;            /* Output of stat() on database file */

    /* zPath is a path to a WAL or journal file. The following block derives
    ** the path to the associated database file from zPath. This block handles
    ** the following naming conventions:
    **
    **   "<path to db>-journal"
    **   "<path to db>-wal"
    **   "<path to db>-journalNN"
    **   "<path to db>-walNN"
    **
    ** where NN is a 4 digit decimal number. The NN naming schemes are 
    ** used by the test_multiplex.c module.
    */
    nDb = sqlite3Strlen30(zPath) - 1; 
    while( nDb>0 && zPath[nDb]!='-' ) nDb--;
    if( nDb==0 ) return SQLITE_OK;
    memcpy(zDb, zPath, nDb);
    zDb[nDb] = '\0';

    if( 0==stat(zDb, &sStat) ){
      *pMode = sStat.st_mode & 0777;
    }else{
      rc = SQLITE_IOERR_FSTAT;
    }
  }else if( flags & SQLITE_OPEN_DELETEONCLOSE ){
    *pMode = 0600;
  }
  return rc;
}