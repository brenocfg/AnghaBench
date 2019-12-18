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

/* Variables and functions */
 int /*<<< orphan*/  STREQ (char*,char*) ; 
 int col ; 
 int /*<<< orphan*/  col_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  col_output (scalar_t__) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int show_range ; 
 int /*<<< orphan*/  show_total () ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strlen (char*) ; 
 int total_mmm ; 
 scalar_t__ total_shown ; 
 scalar_t__ verbose ; 

void
show_area_being_processed(char *area, int n)
{
  static char *last_area = NULL;

  if (verbose < 0)
    return;
  if (last_area) {
    if (total_shown)
      show_total();
    fputs(")", stdout);
    col += 1;
  }

  if (!last_area || !STREQ(area, last_area)) {
    if (last_area) {
      col_cleanup(0);
      total_shown = 0;
      total_mmm = show_range + 1;
    }
    (void) col_output(strlen(area) + 2);
    fprintf(stdout, "[%s", area);
    last_area = area;
  }

  fputs(" (", stdout);
  col += 2;
  show_range = n;
  total_mmm = n + 1;

  fflush(stdout);
}