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
struct TYPE_2__ {int hstart; int hend; char** hist; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAX_HISTORY_SIZE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  get_history_path (char*) ; 
 TYPE_1__ history ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/  tfree (char*) ; 

void write_history() {
  char f_history[128];
  get_history_path(f_history);

  FILE *f = fopen(f_history, "w");
  if (f == NULL) {
    fprintf(stderr, "Opening file %s\n", f_history);
    return;
  }

  for (int i = history.hstart; i != history.hend;) {
    if (history.hist[i] != NULL) {
      fprintf(f, "%s\n", history.hist[i]);
      tfree(history.hist[i]);
    }
    i = (i + 1) % MAX_HISTORY_SIZE;
  }
  fclose(f);
}