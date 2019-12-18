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
struct TYPE_2__ {int hstart; size_t hend; int /*<<< orphan*/ * hist; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAX_HISTORY_SIZE ; 
 int /*<<< orphan*/  R_OK ; 
 int TSDB_FILENAME_LEN ; 
 int access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_history_path (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 TYPE_1__ history ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strdup (char*) ; 

void read_history() {
  // Initialize history
  memset(history.hist, 0, sizeof(char *) * MAX_HISTORY_SIZE);
  history.hstart = 0;
  history.hend = 0;
  char * line = NULL;
  size_t line_size = 0;
  int    read_size = 0;

  char f_history[TSDB_FILENAME_LEN];
  get_history_path(f_history);

  if (access(f_history, R_OK) == -1) {
    return;
  }

  FILE *f = fopen(f_history, "r");
  if (f == NULL) {
    fprintf(stderr, "Opening file %s\n", f_history);
    return;
  }

  while ((read_size = getline(&line, &line_size, f)) != -1) {
    line[read_size - 1] = '\0';
    history.hist[history.hend] = strdup(line);

    history.hend = (history.hend + 1) % MAX_HISTORY_SIZE;

    if (history.hend == history.hstart) {
      history.hstart = (history.hstart + 1) % MAX_HISTORY_SIZE;
    }
  }

  free(line);
  fclose(f);
}