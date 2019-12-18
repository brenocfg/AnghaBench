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
typedef  int /*<<< orphan*/  ticker_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int active_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int) ; 

__attribute__((used)) static void
print_active_time (FILE *f, ticker_t ticker)
{
  int msecs;

  msecs = active_time (ticker);
  fprintf (f, "%d.%06d", msecs / 1000000, msecs % 1000000);
}