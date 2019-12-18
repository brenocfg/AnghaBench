#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* emulation_name; } ;
typedef  TYPE_1__ ld_emulation_xfer_type ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_1__** ld_emulations ; 

void
ldemul_list_emulations (FILE *f)
{
  ld_emulation_xfer_type **eptr = ld_emulations;
  bfd_boolean first = TRUE;

  for (; *eptr; eptr++)
    {
      if (first)
	first = FALSE;
      else
	fprintf (f, " ");
      fprintf (f, "%s", (*eptr)->emulation_name);
    }
}