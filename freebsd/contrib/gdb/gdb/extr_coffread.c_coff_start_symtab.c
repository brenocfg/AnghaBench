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
 int /*<<< orphan*/  record_debugformat (char*) ; 
 int /*<<< orphan*/  savestring (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_symtab (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
coff_start_symtab (char *name)
{
  start_symtab (
  /* We fill in the filename later.  start_symtab puts
     this pointer into last_source_file and we put it in
     subfiles->name, which end_symtab frees; that's why
     it must be malloc'd.  */
		 savestring (name, strlen (name)),
  /* We never know the directory name for COFF.  */
		 NULL,
  /* The start address is irrelevant, since we set
     last_source_start_addr in coff_end_symtab.  */
		 0);
  record_debugformat ("COFF");
}