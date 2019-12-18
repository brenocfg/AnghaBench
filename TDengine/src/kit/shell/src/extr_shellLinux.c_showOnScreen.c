#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct winsize {int ws_col; scalar_t__ ws_row; } ;
struct TYPE_3__ {int commandSize; int screenOffset; int endOffset; int /*<<< orphan*/  command; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ Command ;

/* Variables and functions */
 char* CONTINUE_PROMPT ; 
 int /*<<< orphan*/  DOWN ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  LEFT ; 
 int /*<<< orphan*/  MAX_COMMAND_SIZE ; 
 int /*<<< orphan*/  MB_CUR_MAX ; 
 char* PROMPT_HEADER ; 
 int /*<<< orphan*/  RIGHT ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int /*<<< orphan*/  UP ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct winsize*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int mbtowc (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  positionCursor (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 
 int prompt_size ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int wcwidth (int /*<<< orphan*/ ) ; 

void showOnScreen(Command *cmd) {
  struct winsize w;
  if (ioctl(0, TIOCGWINSZ, &w) < 0 || w.ws_col == 0 || w.ws_row == 0) {
    fprintf(stderr, "No stream device\n");
    exit(EXIT_FAILURE);
  }

  wchar_t wc;
  int size = 0;

  // Print out the command.
  char *total_string = malloc(MAX_COMMAND_SIZE);
  memset(total_string, '\0', MAX_COMMAND_SIZE);
  if (strcmp(cmd->buffer, "") == 0) {
    sprintf(total_string, "%s%s", PROMPT_HEADER, cmd->command);
  } else {
    sprintf(total_string, "%s%s", CONTINUE_PROMPT, cmd->command);
  }

  int remain_column = w.ws_col;
  /* size = cmd->commandSize + prompt_size; */
  for (char *str = total_string; size < cmd->commandSize + prompt_size;) {
    int ret = mbtowc(&wc, str, MB_CUR_MAX);
    if (ret < 0) break;
    size += ret;
    /* assert(size >= 0); */
    int width = wcwidth(wc);
    if (remain_column > width) {
      printf("%lc", wc);
      remain_column -= width;
    } else {
      if (remain_column == width) {
        printf("%lc\n\r", wc);
        remain_column = w.ws_col;
      } else {
        printf("\n\r%lc", wc);
        remain_column = w.ws_col - width;
      }
    }

    str = total_string + size;
  }

  free(total_string);
  /* for (int i = 0; i < size; i++){ */
  /*     char c = total_string[i]; */
  /*     if (k % w.ws_col == 0) { */
  /*         printf("%c\n\r", c); */
  /*     } */
  /*     else { */
  /*         printf("%c", c); */
  /*     } */
  /*     k += 1; */
  /* } */

  // Position the cursor
  int cursor_pos = cmd->screenOffset + prompt_size;
  int ecmd_pos = cmd->endOffset + prompt_size;

  int cursor_x = cursor_pos / w.ws_col;
  int cursor_y = cursor_pos % w.ws_col;
  // int cursor_y = cursor % w.ws_col;
  int command_x = ecmd_pos / w.ws_col;
  int command_y = ecmd_pos % w.ws_col;
  // int command_y = (command.size() + prompt_size) % w.ws_col;
  positionCursor(command_y, LEFT);
  positionCursor(command_x, UP);
  positionCursor(cursor_x, DOWN);
  positionCursor(cursor_y, RIGHT);
  fflush(stdout);
}