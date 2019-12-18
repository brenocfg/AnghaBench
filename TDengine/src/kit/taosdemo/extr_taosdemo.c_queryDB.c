#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  TAOS ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  taos_close (int /*<<< orphan*/ *) ; 
 char* taos_errstr (int /*<<< orphan*/ *) ; 
 scalar_t__ taos_query (int /*<<< orphan*/ *,char*) ; 

void queryDB(TAOS *taos, char *command) {
  int i = 5;
  while (i > 0) {
    if (taos_query(taos, command) == 0) break;
    i--; 
  }
  if (i == 0) {
    fprintf(stderr, "Failed to run %s, reason: %s\n", command, taos_errstr(taos));
    taos_close(taos);
    exit(EXIT_FAILURE);
  }
}