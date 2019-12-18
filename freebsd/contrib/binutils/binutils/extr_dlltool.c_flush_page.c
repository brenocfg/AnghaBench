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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* ASM_C ; 
 char* ASM_LONG ; 
 char* ASM_SHORT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,int,...) ; 

__attribute__((used)) static void
flush_page (FILE *f, long *need, int page_addr, int on_page)
{
  int i;

  /* Flush this page.  */
  fprintf (f, "\t%s\t0x%08x\t%s Starting RVA for chunk\n",
	   ASM_LONG,
	   page_addr,
	   ASM_C);
  fprintf (f, "\t%s\t0x%x\t%s Size of block\n",
	   ASM_LONG,
	   (on_page * 2) + (on_page & 1) * 2 + 8,
	   ASM_C);

  for (i = 0; i < on_page; i++)
    {
      long needed = need[i];

      if (needed)
	needed = ((needed - page_addr) | 0x3000) & 0xffff;

      fprintf (f, "\t%s\t0x%lx\n", ASM_SHORT, needed);
    }

  /* And padding */
  if (on_page & 1)
    fprintf (f, "\t%s\t0x%x\n", ASM_SHORT, 0 | 0x0000);
}