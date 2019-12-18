#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * buffer; } ;
struct TYPE_6__ {int id; int /*<<< orphan*/  email; int /*<<< orphan*/  username; } ;
struct TYPE_7__ {TYPE_1__ row_to_insert; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ Statement ;
typedef  int /*<<< orphan*/  PrepareResult ;
typedef  TYPE_3__ InputBuffer ;

/* Variables and functions */
 scalar_t__ COLUMN_EMAIL_SIZE ; 
 scalar_t__ COLUMN_USERNAME_SIZE ; 
 int /*<<< orphan*/  PREPARE_NEGATIVE_ID ; 
 int /*<<< orphan*/  PREPARE_STRING_TOO_LONG ; 
 int /*<<< orphan*/  PREPARE_SUCCESS ; 
 int /*<<< orphan*/  PREPARE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  STATEMENT_INSERT ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char*) ; 
 char* strtok (int /*<<< orphan*/ *,char*) ; 

PrepareResult prepare_insert(InputBuffer* input_buffer, Statement* statement) {
  statement->type = STATEMENT_INSERT;

  char* keyword = strtok(input_buffer->buffer, " ");
  char* id_string = strtok(NULL, " ");
  char* username = strtok(NULL, " ");
  char* email = strtok(NULL, " ");

  if (id_string == NULL || username == NULL || email == NULL) {
    return PREPARE_SYNTAX_ERROR;
  }

  int id = atoi(id_string);
  if (id < 0) {
    return PREPARE_NEGATIVE_ID;
  }
  if (strlen(username) > COLUMN_USERNAME_SIZE) {
    return PREPARE_STRING_TOO_LONG;
  }
  if (strlen(email) > COLUMN_EMAIL_SIZE) {
    return PREPARE_STRING_TOO_LONG;
  }

  statement->row_to_insert.id = id;
  strcpy(statement->row_to_insert.username, username);
  strcpy(statement->row_to_insert.email, email);

  return PREPARE_SUCCESS;
}