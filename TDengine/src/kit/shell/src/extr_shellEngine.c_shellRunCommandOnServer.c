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
struct TYPE_4__ {char** we_wordv; } ;
typedef  TYPE_1__ wordexp_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  TAOS ;

/* Variables and functions */
 int REG_EXTENDED ; 
 int REG_ICASE ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ regex_match (char*,char*,int) ; 
 int shellDumpResult (int /*<<< orphan*/ *,char*,int*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* strstr (char*,char*) ; 
 int taosGetTimestampUs () ; 
 int taos_affected_rows (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taos_error (int /*<<< orphan*/ *) ; 
 char* taos_errstr (int /*<<< orphan*/ *) ; 
 int taos_field_count (int /*<<< orphan*/ *) ; 
 scalar_t__ taos_query (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ wordexp (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wordfree (TYPE_1__*) ; 

void shellRunCommandOnServer(TAOS *con, char command[]) {
  int64_t   st, et;
  wordexp_t full_path;
  char *    sptr = NULL;
  char *    cptr = NULL;
  char *    fname = NULL;
  bool      printMode = false;

  if ((sptr = strstr(command, ">>")) != NULL) {
    cptr = strstr(command, ";");
    if (cptr != NULL) {
      *cptr = '\0';
    }

    if (wordexp(sptr + 2, &full_path, 0) != 0) {
      fprintf(stderr, "ERROR: invalid filename: %s\n", sptr + 2);
      return;
    }
    *sptr = '\0';
    fname = full_path.we_wordv[0];
  }

  if ((sptr = strstr(command, "\\G")) != NULL) {
    cptr = strstr(command, ";");
    if (cptr != NULL) {
      *cptr = '\0';
    }

    *sptr = '\0';
    printMode = true;  // When output to a file, the switch does not work.
  }

  st = taosGetTimestampUs();

  if (taos_query(con, command)) {
    taos_error(con);
    return;
  }

  if (regex_match(command, "^\\s*use\\s+[a-zA-Z0-9]+\\s*;\\s*$", REG_EXTENDED | REG_ICASE)) {
    fprintf(stdout, "Database changed.\n\n");
    fflush(stdout);
    return;
  }

  int num_fields = taos_field_count(con);
  if (num_fields != 0) {  // select and show kinds of commands
    int error_no = 0;
    int numOfRows = shellDumpResult(con, fname, &error_no, printMode);
    if (numOfRows < 0) return;

    et = taosGetTimestampUs();
    if (error_no == 0) {
      printf("Query OK, %d row(s) in set (%.6fs)\n", numOfRows, (et - st) / 1E6);
    } else {
      printf("Query interrupted (%s), %d row(s) in set (%.6fs)\n", taos_errstr(con), numOfRows, (et - st) / 1E6);
    }
  } else {
    int num_rows_affacted = taos_affected_rows(con);
    et = taosGetTimestampUs();
    printf("Query OK, %d row(s) affected (%.6fs)\n", num_rows_affacted, (et - st) / 1E6);
  }

  printf("\n");

  if (fname != NULL) {
    wordfree(&full_path);
  }
  return;
}