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
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER2 (int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sqlite3_changes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3_context_db_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void changes(
  sqlite3_context *context,
  int NotUsed,
  sqlite3_value **NotUsed2
){
  sqlite3 *db = sqlite3_context_db_handle(context);
  UNUSED_PARAMETER2(NotUsed, NotUsed2);
  sqlite3_result_int(context, sqlite3_changes(db));
}