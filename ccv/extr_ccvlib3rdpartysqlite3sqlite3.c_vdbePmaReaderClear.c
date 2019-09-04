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
struct TYPE_4__ {int /*<<< orphan*/  pIncr; scalar_t__ aMap; int /*<<< orphan*/  pFd; int /*<<< orphan*/  aBuffer; int /*<<< orphan*/  aAlloc; } ;
typedef  TYPE_1__ PmaReader ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3OsUnfetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdbeIncrFree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vdbePmaReaderClear(PmaReader *pReadr){
  sqlite3_free(pReadr->aAlloc);
  sqlite3_free(pReadr->aBuffer);
  if( pReadr->aMap ) sqlite3OsUnfetch(pReadr->pFd, 0, pReadr->aMap);
  vdbeIncrFree(pReadr->pIncr);
  memset(pReadr, 0, sizeof(PmaReader));
}