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
typedef  int /*<<< orphan*/  n ;

/* Variables and functions */
 scalar_t__ col_output (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int show_range ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char*) ; 
 int total_mmm ; 
 int /*<<< orphan*/  total_shown ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
show_total(void)
{
  if (total_mmm != -show_range + 1) {
    char n[8];
    int len;

    if (total_mmm < 0)
      fputc('*', stdout);
    xsnprintf(n, sizeof(n), "%d", total_shown);
    len = strlen(n);
    if (col_output(len))
      fputc(' ', stdout);
    fputs(n, stdout);
    fflush(stdout);
    total_mmm = -show_range;
  }
}