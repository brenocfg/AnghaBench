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
 scalar_t__ col ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_total () ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ verbose ; 

void
col_cleanup(int eoj)
{
  if (verbose < 0)
    return;
  if (eoj) {
    show_total();
    fputs(")]", stdout);
  }
  if (col) {
    fputc('\n', stdout);
    col = 0;
  }
}