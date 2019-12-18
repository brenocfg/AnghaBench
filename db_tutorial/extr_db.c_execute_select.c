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
typedef  int /*<<< orphan*/  Table ;
struct TYPE_6__ {int /*<<< orphan*/  end_of_table; } ;
typedef  int /*<<< orphan*/  Statement ;
typedef  int /*<<< orphan*/  Row ;
typedef  int /*<<< orphan*/  ExecuteResult ;
typedef  TYPE_1__ Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  EXECUTE_SUCCESS ; 
 int /*<<< orphan*/  cursor_advance (TYPE_1__*) ; 
 int /*<<< orphan*/  cursor_value (TYPE_1__*) ; 
 int /*<<< orphan*/  deserialize_row (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  print_row (int /*<<< orphan*/ *) ; 
 TYPE_1__* table_start (int /*<<< orphan*/ *) ; 

ExecuteResult execute_select(Statement* statement, Table* table) {
  Cursor* cursor = table_start(table);

  Row row;
  while (!(cursor->end_of_table)) {
    deserialize_row(cursor_value(cursor), &row);
    print_row(&row);
    cursor_advance(cursor);
  }

  free(cursor);

  return EXECUTE_SUCCESS;
}