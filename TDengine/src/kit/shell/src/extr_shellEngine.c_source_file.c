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
typedef  int /*<<< orphan*/  TAOS ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAX_COMMAND_SIZE ; 
 char* PROMPT_HEADER ; 
 int /*<<< orphan*/  R_OK ; 
 int access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ isCommentLine (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  shellRunCommand (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ wordexp (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wordfree (TYPE_1__*) ; 

void source_file(TAOS *con, char *fptr) {
  wordexp_t full_path;
  int       read_len = 0;
  char *    cmd = malloc(MAX_COMMAND_SIZE);
  size_t    cmd_len = 0;
  char *    line = NULL;
  size_t    line_len = 0;

  if (wordexp(fptr, &full_path, 0) != 0) {
    fprintf(stderr, "ERROR: illegal file name\n");
    return;
  }

  char *fname = full_path.we_wordv[0];

  if (access(fname, R_OK) == -1) {
    fprintf(stderr, "ERROR: file %s is not readable\n", fptr);
    wordfree(&full_path);
    return;
  }

  FILE *f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "ERROR: failed to open file %s\n", fname);
    wordfree(&full_path);
    return;
  }

  while ((read_len = getline(&line, &line_len, f)) != -1) {
    if (read_len >= MAX_COMMAND_SIZE) continue;
    line[--read_len] = '\0';

    if (read_len == 0 || isCommentLine(line)) {  // line starts with #
      continue;
    }

    if (line[read_len - 1] == '\\') {
      line[read_len - 1] = ' ';
      memcpy(cmd + cmd_len, line, read_len);
      cmd_len += read_len;
      continue;
    }

    memcpy(cmd + cmd_len, line, read_len);
    printf("%s%s\n", PROMPT_HEADER, cmd);
    shellRunCommand(con, cmd);
    memset(cmd, 0, MAX_COMMAND_SIZE);
    cmd_len = 0;
  }

  free(cmd);
  if (line) free(line);
  wordfree(&full_path);
  fclose(f);
}