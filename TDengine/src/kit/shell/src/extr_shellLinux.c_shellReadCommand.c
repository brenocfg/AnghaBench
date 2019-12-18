#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_16__ {char* buffer; char* command; } ;
struct TYPE_15__ {unsigned int hend; unsigned int hstart; char** hist; } ;
typedef  int /*<<< orphan*/  TAOS ;
typedef  TYPE_1__ Command ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_COMMAND_SIZE ; 
 unsigned int MAX_HISTORY_SIZE ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  backspaceChar (TYPE_1__*) ; 
 scalar_t__ calloc (int,int /*<<< orphan*/ ) ; 
 int countPrefixOnes (char) ; 
 int /*<<< orphan*/  deleteChar (TYPE_1__*) ; 
 int /*<<< orphan*/  exitShell () ; 
 char getchar () ; 
 TYPE_12__ history ; 
 int /*<<< orphan*/  insertChar (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  isReadyGo (TYPE_1__*) ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  moveCursorLeft (TYPE_1__*) ; 
 int /*<<< orphan*/  moveCursorRight (TYPE_1__*) ; 
 int /*<<< orphan*/  positionCursorEnd (TYPE_1__*) ; 
 int /*<<< orphan*/  positionCursorHome (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  resetCommand (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  showOnScreen (TYPE_1__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  system (char*) ; 
 int /*<<< orphan*/  taos_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tfree (char*) ; 
 int /*<<< orphan*/  updateBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  write_history () ; 

void shellReadCommand(TAOS *con, char *command) {
  unsigned hist_counter = history.hend;
  char utf8_array[10] = "\0";
  Command cmd;
  memset(&cmd, 0, sizeof(cmd));
  cmd.buffer = (char *)calloc(1, MAX_COMMAND_SIZE);
  cmd.command = (char *)calloc(1, MAX_COMMAND_SIZE);
  showOnScreen(&cmd);

  // Read input.
  char c;
  while (1) {
    c = getchar();

    if (c < 0) {  // For UTF-8
      int count = countPrefixOnes(c);
      utf8_array[0] = c;
      for (int k = 1; k < count; k++) {
        c = getchar();
        utf8_array[k] = c;
      }
      insertChar(&cmd, utf8_array, count);
    } else if (c < '\033') {
      // Ctrl keys.  TODO: Implement ctrl combinations
      switch (c) {
        case 1:  // ctrl A
          positionCursorHome(&cmd);
          break;
        case 3:
          printf("\n");
          resetCommand(&cmd, "");
          kill(0, SIGINT);
          break;
        case 4:  // EOF or Ctrl+D
          printf("\n");
          taos_close(con);
          // write the history
          write_history();
          exitShell();
          break;
        case 5:  // ctrl E
          positionCursorEnd(&cmd);
          break;
        case 8:
          backspaceChar(&cmd);
          break;
        case '\n':
        case '\r':
          printf("\n");
          if (isReadyGo(&cmd)) {
            sprintf(command, "%s%s", cmd.buffer, cmd.command);
            tfree(cmd.buffer);
            tfree(cmd.command);
            return;
          } else {
            updateBuffer(&cmd);
          }
          break;
        case 12:  // Ctrl + L;
          system("clear");
          showOnScreen(&cmd);
          break;
      }
    } else if (c == '\033') {
      c = getchar();
      switch (c) {
        case '[':
          c = getchar();
          switch (c) {
            case 'A':  // Up arrow
              if (hist_counter != history.hstart) {
                hist_counter = (hist_counter + MAX_HISTORY_SIZE - 1) % MAX_HISTORY_SIZE;
                resetCommand(&cmd, (history.hist[hist_counter] == NULL) ? "" : history.hist[hist_counter]);
              }
              break;
            case 'B':  // Down arrow
              if (hist_counter != history.hend) {
                int next_hist = (hist_counter + 1) % MAX_HISTORY_SIZE;

                if (next_hist != history.hend) {
                  resetCommand(&cmd, (history.hist[next_hist] == NULL) ? "" : history.hist[next_hist]);
                } else {
                  resetCommand(&cmd, "");
                }
                hist_counter = next_hist;
              }
              break;
            case 'C':  // Right arrow
              moveCursorRight(&cmd);
              break;
            case 'D':  // Left arrow
              moveCursorLeft(&cmd);
              break;
            case '1':
              if ((c = getchar()) == '~') {
                // Home key
                positionCursorHome(&cmd);
              }
              break;
            case '2':
              if ((c = getchar()) == '~') {
                // Insert key
              }
              break;
            case '3':
              if ((c = getchar()) == '~') {
                // Delete key
                deleteChar(&cmd);
              }
              break;
            case '4':
              if ((c = getchar()) == '~') {
                // End key
                positionCursorEnd(&cmd);
              }
              break;
            case '5':
              if ((c = getchar()) == '~') {
                // Page up key
              }
              break;
            case '6':
              if ((c = getchar()) == '~') {
                // Page down key
              }
              break;
            case 72:
              // Home key
              positionCursorHome(&cmd);
              break;
            case 70:
              // End key
              positionCursorEnd(&cmd);
              break;
          }
          break;
      }
    } else if (c == 0x7f) {
      // press delete key
      backspaceChar(&cmd);
    } else {
      insertChar(&cmd, &c, 1);
    }
  }
}