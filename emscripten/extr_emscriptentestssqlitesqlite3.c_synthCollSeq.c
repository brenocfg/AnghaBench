#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_6__ {char* zName; scalar_t__ xCmp; scalar_t__ xDel; } ;
typedef  TYPE_1__ CollSeq ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
#define  SQLITE_UTF16BE 130 
#define  SQLITE_UTF16LE 129 
#define  SQLITE_UTF8 128 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 TYPE_1__* sqlite3FindCollSeq (int /*<<< orphan*/ *,int /*<<< orphan*/  const,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int synthCollSeq(sqlite3 *db, CollSeq *pColl){
  CollSeq *pColl2;
  char *z = pColl->zName;
  int i;
  static const u8 aEnc[] = { SQLITE_UTF16BE, SQLITE_UTF16LE, SQLITE_UTF8 };
  for(i=0; i<3; i++){
    pColl2 = sqlite3FindCollSeq(db, aEnc[i], z, 0);
    if( pColl2->xCmp!=0 ){
      memcpy(pColl, pColl2, sizeof(CollSeq));
      pColl->xDel = 0;         /* Do not copy the destructor */
      return SQLITE_OK;
    }
  }
  return SQLITE_ERROR;
}