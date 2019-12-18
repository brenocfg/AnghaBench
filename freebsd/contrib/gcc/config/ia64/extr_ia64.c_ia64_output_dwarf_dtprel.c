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
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  output_addr_const (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ia64_output_dwarf_dtprel (FILE *file, int size, rtx x)
{
  gcc_assert (size == 4 || size == 8);
  if (size == 4)
    fputs ("\tdata4.ua\t@dtprel(", file);
  else
    fputs ("\tdata8.ua\t@dtprel(", file);
  output_addr_const (file, x);
  fputs (")", file);
}