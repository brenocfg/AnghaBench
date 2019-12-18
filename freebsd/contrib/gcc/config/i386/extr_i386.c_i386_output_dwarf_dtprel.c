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
 char* ASM_LONG ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  output_addr_const (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
i386_output_dwarf_dtprel (FILE *file, int size, rtx x)
{
  fputs (ASM_LONG, file);
  output_addr_const (file, x);
  fputs ("@DTPOFF", file);
  switch (size)
    {
    case 4:
      break;
    case 8:
      fputs (", 0", file);
      break;
    default:
      gcc_unreachable ();
   }
}