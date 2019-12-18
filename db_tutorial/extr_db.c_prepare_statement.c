#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_7__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ Statement ;
typedef  int /*<<< orphan*/  PrepareResult ;
typedef  TYPE_2__ InputBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  PREPARE_SUCCESS ; 
 int /*<<< orphan*/  PREPARE_UNRECOGNIZED_STATEMENT ; 
 int /*<<< orphan*/  STATEMENT_SELECT ; 
 int /*<<< orphan*/  prepare_insert (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

PrepareResult prepare_statement(InputBuffer* input_buffer,
                                Statement* statement) {
  if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
    return prepare_insert(input_buffer, statement);
  }
  if (strcmp(input_buffer->buffer, "select") == 0) {
    statement->type = STATEMENT_SELECT;
    return PREPARE_SUCCESS;
  }

  return PREPARE_UNRECOGNIZED_STATEMENT;
}