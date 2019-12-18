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
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int flag_simple ; 
 int /*<<< orphan*/  print_rtl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
print_simple_rtl (FILE *outf, rtx x)
{
  flag_simple = 1;
  print_rtl (outf, x);
  flag_simple = 0;
}