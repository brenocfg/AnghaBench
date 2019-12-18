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
 int col ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 scalar_t__ show_range ; 
 int /*<<< orphan*/  show_total () ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ total_mmm ; 
 int /*<<< orphan*/  total_shown ; 
 scalar_t__ verbose ; 

void
show_new(char *msg)
{
  if (verbose < 0)
    return;

  total_shown++;
  if (total_mmm > show_range) {
    show_total();
  } else if (total_mmm == 0) {
    fputc('*', stdout);
    fflush(stdout);
    col += 1;
  }
  total_mmm++;
}