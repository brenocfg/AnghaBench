#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int bfd_print_symbol_type ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_6__ {char* name; TYPE_1__* section; } ;
typedef  TYPE_2__ asymbol ;
struct TYPE_5__ {char* name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  bfd_print_symbol_name 128 
 int /*<<< orphan*/  bfd_print_symbol_vandf (int /*<<< orphan*/ *,void*,TYPE_2__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,...) ; 

__attribute__((used)) static void
srec_print_symbol (bfd *abfd,
		   void * afile,
		   asymbol *symbol,
		   bfd_print_symbol_type how)
{
  FILE *file = (FILE *) afile;

  switch (how)
    {
    case bfd_print_symbol_name:
      fprintf (file, "%s", symbol->name);
      break;
    default:
      bfd_print_symbol_vandf (abfd, (void *) file, symbol);
      fprintf (file, " %-5s %s",
	       symbol->section->name,
	       symbol->name);
    }
}