#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int ordinal; scalar_t__ name; TYPE_1__* module; scalar_t__ internal_name; } ;
typedef  TYPE_4__ def_file_import ;
struct TYPE_12__ {int ordinal; scalar_t__ flag_data; scalar_t__ flag_noname; scalar_t__ flag_constant; scalar_t__ flag_private; scalar_t__ internal_name; scalar_t__ name; } ;
typedef  TYPE_5__ def_file_export ;
struct TYPE_9__ {scalar_t__ ImageBase; } ;
struct TYPE_14__ {TYPE_2__ pe_opthdr; } ;
struct TYPE_13__ {int version_minor; int version_major; int stack_reserve; int heap_reserve; int stack_commit; int heap_commit; int num_section_defs; int num_exports; int num_imports; TYPE_4__* imports; TYPE_5__* exports; TYPE_3__* section_defs; scalar_t__ description; scalar_t__ name; scalar_t__ is_dll; } ;
struct TYPE_10__ {scalar_t__ flag_shared; scalar_t__ flag_execute; scalar_t__ flag_write; scalar_t__ flag_read; scalar_t__ class; scalar_t__ name; } ;
struct TYPE_8__ {scalar_t__ name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  einfo (char*,char const*,...) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  output_bfd ; 
 TYPE_7__* pe_data (int /*<<< orphan*/ ) ; 
 TYPE_6__* pe_def_file ; 
 int /*<<< orphan*/  program_name ; 
 int /*<<< orphan*/  quoteput (scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (scalar_t__,scalar_t__) ; 

void
pe_dll_generate_def_file (const char *pe_out_def_filename)
{
  int i;
  FILE *out = fopen (pe_out_def_filename, "w");

  if (out == NULL)
    /* xgettext:c-format */
    einfo (_("%s: Can't open output def file %s\n"),
	   program_name, pe_out_def_filename);

  if (pe_def_file)
    {
      if (pe_def_file->name)
	{
	  if (pe_def_file->is_dll)
	    fprintf (out, "LIBRARY ");
	  else
	    fprintf (out, "NAME ");

	  quoteput (pe_def_file->name, out, 1);

	  if (pe_data (output_bfd)->pe_opthdr.ImageBase)
	    fprintf (out, " BASE=0x%lx",
		     (unsigned long) pe_data (output_bfd)->pe_opthdr.ImageBase);
	  fprintf (out, "\n");
	}

      if (pe_def_file->description)
	{
	  fprintf (out, "DESCRIPTION ");
	  quoteput (pe_def_file->description, out, 1);
	  fprintf (out, "\n");
	}

      if (pe_def_file->version_minor != -1)
	fprintf (out, "VERSION %d.%d\n", pe_def_file->version_major,
		 pe_def_file->version_minor);
      else if (pe_def_file->version_major != -1)
	fprintf (out, "VERSION %d\n", pe_def_file->version_major);

      if (pe_def_file->stack_reserve != -1 || pe_def_file->heap_reserve != -1)
	fprintf (out, "\n");

      if (pe_def_file->stack_commit != -1)
	fprintf (out, "STACKSIZE 0x%x,0x%x\n",
		 pe_def_file->stack_reserve, pe_def_file->stack_commit);
      else if (pe_def_file->stack_reserve != -1)
	fprintf (out, "STACKSIZE 0x%x\n", pe_def_file->stack_reserve);

      if (pe_def_file->heap_commit != -1)
	fprintf (out, "HEAPSIZE 0x%x,0x%x\n",
		 pe_def_file->heap_reserve, pe_def_file->heap_commit);
      else if (pe_def_file->heap_reserve != -1)
	fprintf (out, "HEAPSIZE 0x%x\n", pe_def_file->heap_reserve);

      if (pe_def_file->num_section_defs > 0)
	{
	  fprintf (out, "\nSECTIONS\n\n");

	  for (i = 0; i < pe_def_file->num_section_defs; i++)
	    {
	      fprintf (out, "    ");
	      quoteput (pe_def_file->section_defs[i].name, out, 0);

	      if (pe_def_file->section_defs[i].class)
		{
		  fprintf (out, " CLASS ");
		  quoteput (pe_def_file->section_defs[i].class, out, 0);
		}

	      if (pe_def_file->section_defs[i].flag_read)
		fprintf (out, " READ");

	      if (pe_def_file->section_defs[i].flag_write)
		fprintf (out, " WRITE");

	      if (pe_def_file->section_defs[i].flag_execute)
		fprintf (out, " EXECUTE");

	      if (pe_def_file->section_defs[i].flag_shared)
		fprintf (out, " SHARED");

	      fprintf (out, "\n");
	    }
	}

      if (pe_def_file->num_exports > 0)
	{
	  fprintf (out, "EXPORTS\n");

	  for (i = 0; i < pe_def_file->num_exports; i++)
	    {
	      def_file_export *e = pe_def_file->exports + i;
	      fprintf (out, "    ");
	      quoteput (e->name, out, 0);

	      if (e->internal_name && strcmp (e->internal_name, e->name))
		{
		  fprintf (out, " = ");
		  quoteput (e->internal_name, out, 0);
		}

	      if (e->ordinal != -1)
		fprintf (out, " @%d", e->ordinal);

	      if (e->flag_private)
		fprintf (out, " PRIVATE");

	      if (e->flag_constant)
		fprintf (out, " CONSTANT");

	      if (e->flag_noname)
		fprintf (out, " NONAME");

	      if (e->flag_data)
		fprintf (out, " DATA");

	      fprintf (out, "\n");
	    }
	}

      if (pe_def_file->num_imports > 0)
	{
	  fprintf (out, "\nIMPORTS\n\n");

	  for (i = 0; i < pe_def_file->num_imports; i++)
	    {
	      def_file_import *im = pe_def_file->imports + i;
	      fprintf (out, "    ");

	      if (im->internal_name
		  && (!im->name || strcmp (im->internal_name, im->name)))
		{
		  quoteput (im->internal_name, out, 0);
		  fprintf (out, " = ");
		}

	      quoteput (im->module->name, out, 0);
	      fprintf (out, ".");

	      if (im->name)
		quoteput (im->name, out, 0);
	      else
		fprintf (out, "%d", im->ordinal);

	      fprintf (out, "\n");
	    }
	}
    }
  else
    fprintf (out, _("; no contents available\n"));

  if (fclose (out) == EOF)
    /* xgettext:c-format */
    einfo (_("%P: Error closing file `%s'\n"), pe_out_def_filename);
}