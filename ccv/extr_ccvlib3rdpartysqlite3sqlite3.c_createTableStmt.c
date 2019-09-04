#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_4__ {int nCol; TYPE_2__* aCol; int /*<<< orphan*/  zName; } ;
typedef  TYPE_1__ Table ;
struct TYPE_5__ {scalar_t__ affinity; int /*<<< orphan*/  zName; } ;
typedef  TYPE_2__ Column ;

/* Variables and functions */
 scalar_t__ ArraySize (char const* const*) ; 
 scalar_t__ SQLITE_AFF_BLOB ; 
 scalar_t__ SQLITE_AFF_INTEGER ; 
 scalar_t__ SQLITE_AFF_NUMERIC ; 
 scalar_t__ SQLITE_AFF_REAL ; 
 scalar_t__ SQLITE_AFF_TEXT ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ identLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  identPut (char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ sqlite3AffinityType (char const*,int /*<<< orphan*/ ) ; 
 char* sqlite3DbMallocRaw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3OomFault (int /*<<< orphan*/ *) ; 
 int sqlite3Strlen30 (char const*) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,...) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static char *createTableStmt(sqlite3 *db, Table *p){
  int i, k, n;
  char *zStmt;
  char *zSep, *zSep2, *zEnd;
  Column *pCol;
  n = 0;
  for(pCol = p->aCol, i=0; i<p->nCol; i++, pCol++){
    n += identLength(pCol->zName) + 5;
  }
  n += identLength(p->zName);
  if( n<50 ){ 
    zSep = "";
    zSep2 = ",";
    zEnd = ")";
  }else{
    zSep = "\n  ";
    zSep2 = ",\n  ";
    zEnd = "\n)";
  }
  n += 35 + 6*p->nCol;
  zStmt = sqlite3DbMallocRaw(0, n);
  if( zStmt==0 ){
    sqlite3OomFault(db);
    return 0;
  }
  sqlite3_snprintf(n, zStmt, "CREATE TABLE ");
  k = sqlite3Strlen30(zStmt);
  identPut(zStmt, &k, p->zName);
  zStmt[k++] = '(';
  for(pCol=p->aCol, i=0; i<p->nCol; i++, pCol++){
    static const char * const azType[] = {
        /* SQLITE_AFF_BLOB    */ "",
        /* SQLITE_AFF_TEXT    */ " TEXT",
        /* SQLITE_AFF_NUMERIC */ " NUM",
        /* SQLITE_AFF_INTEGER */ " INT",
        /* SQLITE_AFF_REAL    */ " REAL"
    };
    int len;
    const char *zType;

    sqlite3_snprintf(n-k, &zStmt[k], zSep);
    k += sqlite3Strlen30(&zStmt[k]);
    zSep = zSep2;
    identPut(zStmt, &k, pCol->zName);
    assert( pCol->affinity-SQLITE_AFF_BLOB >= 0 );
    assert( pCol->affinity-SQLITE_AFF_BLOB < ArraySize(azType) );
    testcase( pCol->affinity==SQLITE_AFF_BLOB );
    testcase( pCol->affinity==SQLITE_AFF_TEXT );
    testcase( pCol->affinity==SQLITE_AFF_NUMERIC );
    testcase( pCol->affinity==SQLITE_AFF_INTEGER );
    testcase( pCol->affinity==SQLITE_AFF_REAL );
    
    zType = azType[pCol->affinity - SQLITE_AFF_BLOB];
    len = sqlite3Strlen30(zType);
    assert( pCol->affinity==SQLITE_AFF_BLOB 
            || pCol->affinity==sqlite3AffinityType(zType, 0) );
    memcpy(&zStmt[k], zType, len);
    k += len;
    assert( k<=n );
  }
  sqlite3_snprintf(n-k, &zStmt[k], "%s", zEnd);
  return zStmt;
}