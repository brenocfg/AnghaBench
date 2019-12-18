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
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_5__ {struct TYPE_5__* zColAff; } ;
typedef  TYPE_1__ Index ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3DeleteIndexSamples (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void freeIndex(sqlite3 *db, Index *p){
#ifndef SQLITE_OMIT_ANALYZE
  sqlite3DeleteIndexSamples(db, p);
#endif
  sqlite3DbFree(db, p->zColAff);
  sqlite3DbFree(db, p);
}