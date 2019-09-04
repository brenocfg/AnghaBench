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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  CollSeq ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/ * sqlite3GetFuncCollSeq (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3MemCompare (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nullifFunc(
  sqlite3_context *context,
  int NotUsed,
  sqlite3_value **argv
){
  CollSeq *pColl = sqlite3GetFuncCollSeq(context);
  UNUSED_PARAMETER(NotUsed);
  if( sqlite3MemCompare(argv[0], argv[1], pColl)!=0 ){
    sqlite3_result_value(context, argv[0]);
  }
}