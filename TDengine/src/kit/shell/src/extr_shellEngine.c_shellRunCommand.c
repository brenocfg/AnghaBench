#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int hstart; int hend; int /*<<< orphan*/ ** hist; } ;
typedef  int /*<<< orphan*/  TAOS ;

/* Variables and functions */
 int MAX_HISTORY_SIZE ; 
 int REG_EXTENDED ; 
 int REG_ICASE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exitShell () ; 
 TYPE_1__ history ; 
 scalar_t__ regex_match (char*,char*,int) ; 
 int /*<<< orphan*/  shellReplaceCtrlChar (char*) ; 
 int /*<<< orphan*/  shellRunCommandOnServer (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  source_file (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 char* strtok (char*,char*) ; 
 int /*<<< orphan*/  system (char*) ; 
 int /*<<< orphan*/  taos_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_history () ; 

void shellRunCommand(TAOS *con, char *command) {
  /* If command is empty just return */
  if (regex_match(command, "^[ \t;]*$", REG_EXTENDED)) {
    return;
  }

  /* Update the history vector. */
  if (history.hstart == history.hend ||
      history.hist[(history.hend + MAX_HISTORY_SIZE - 1) % MAX_HISTORY_SIZE] == NULL ||
      strcmp(command, history.hist[(history.hend + MAX_HISTORY_SIZE - 1) % MAX_HISTORY_SIZE]) != 0) {
    if (history.hist[history.hend] != NULL) {
      tfree(history.hist[history.hend]);
    }
    history.hist[history.hend] = strdup(command);

    history.hend = (history.hend + 1) % MAX_HISTORY_SIZE;
    if (history.hend == history.hstart) {
      history.hstart = (history.hstart + 1) % MAX_HISTORY_SIZE;
    }
  }

  shellReplaceCtrlChar(command);

  // Analyse the command.
  if (regex_match(command, "^[ \t]*(quit|q|exit)[ \t;]*$", REG_EXTENDED | REG_ICASE)) {
    taos_close(con);
    write_history();
    exitShell();
  } else if (regex_match(command, "^[\t ]*clear[ \t;]*$", REG_EXTENDED | REG_ICASE)) {
    // If clear the screen.
    system("clear");
    return;
  } else if (regex_match(command, "^[ \t]*source[\t ]+[^ ]+[ \t;]*$", REG_EXTENDED | REG_ICASE)) {
    /* If source file. */
    char *c_ptr = strtok(command, " ;");
    assert(c_ptr != NULL);
    c_ptr = strtok(NULL, " ;");
    assert(c_ptr != NULL);

    source_file(con, c_ptr);
  } else {
    shellRunCommandOnServer(con, command);
  }
}