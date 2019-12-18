#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct coff_symbol {char* name; TYPE_3__* type; TYPE_2__* where; struct coff_symbol* next; } ;
struct coff_sfile {TYPE_1__* scope; } ;
struct coff_section {char* name; } ;
struct coff_ofile {int nsections; struct coff_section* sections; } ;
struct IT_sc {int format; int align; int read; int write; int exec; int init; int mode; int* name; void* contents; scalar_t__ spare1; scalar_t__ segadd; scalar_t__ spare; int /*<<< orphan*/  concat; scalar_t__ length; scalar_t__ addr; } ;
struct TYPE_6__ {scalar_t__ type; scalar_t__ size; } ;
struct TYPE_5__ {scalar_t__ offset; struct coff_section* section; } ;
struct TYPE_4__ {struct coff_symbol* vars_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONCAT_SIMPLE ; 
 void* CONTENTS_CODE ; 
 void* CONTENTS_DATA ; 
 int EXEC_P ; 
 int /*<<< orphan*/  abfd ; 
 int bfd_get_file_flags (int /*<<< orphan*/ ) ; 
 scalar_t__ calloc (int,int) ; 
 scalar_t__ coff_secdef_type ; 
 int /*<<< orphan*/  file ; 
 int* section_translate (char*) ; 
 int strlen (int*) ; 
 int /*<<< orphan*/  sysroff_swap_sc_out (int /*<<< orphan*/ ,struct IT_sc*) ; 

__attribute__((used)) static int
wr_sc (struct coff_ofile *ptr, struct coff_sfile *sfile)
{
  int i;
  int scount = 0;
  /* First work out the total number of sections.  */
  int total_sec = ptr->nsections;
  struct myinfo
    {
      struct coff_section *sec;
      struct coff_symbol *symbol;
    };
  struct coff_symbol *symbol;
  struct myinfo *info
    = (struct myinfo *) calloc (total_sec, sizeof (struct myinfo));


  for (i = 0; i < total_sec; i++)
    {
      info[i].sec = ptr->sections + i;
      info[i].symbol = 0;
    }

  for (symbol = sfile->scope->vars_head;
       symbol;
       symbol = symbol->next)
    {

      if (symbol->type->type == coff_secdef_type)
	{
	  for (i = 0; i < total_sec; i++)
	    {
	      if (symbol->where->section == info[i].sec)
		{
		  info[i].symbol = symbol;
		  break;
		}
	    }
	}
    }

  /* Now output all the section info, and fake up some stuff for sections
     we don't have.  */
  for (i = 1; i < total_sec; i++)
    {
      struct IT_sc sc;
      char *name;

      symbol = info[i].symbol;
      sc.spare = 0;
      sc.spare1 = 0;

      if (!symbol)
	{
	  /* Don't have a symbol set aside for this section, which means
	     that nothing in this file does anything for the section.  */
	  sc.format = !(bfd_get_file_flags (abfd) & EXEC_P);
	  sc.addr = 0;
	  sc.length = 0;
	  name = info[i].sec->name;
	}
      else
	{
	  if (bfd_get_file_flags (abfd) & EXEC_P)
	    {
	      sc.format = 0;
	      sc.addr = symbol->where->offset;
	    }
	  else
	    {
	      sc.format = 1;
	      sc.addr = 0;
	    }
	  sc.length = symbol->type->size;
	  name = symbol->name;
	}

      sc.align = 4;
      sc.concat = CONCAT_SIMPLE;
      sc.read = 3;
      sc.write = 3;
      sc.exec = 3;
      sc.init = 3;
      sc.mode = 3;
      sc.spare = 0;
      sc.segadd = 0;
      sc.spare1 = 0;		/* If not zero, then it doesn't work.  */
      sc.name = section_translate (name);

      if (strlen (sc.name) == 1)
	{
	  switch (sc.name[0])
	    {
	    case 'D':
	    case 'B':
	      sc.contents = CONTENTS_DATA;
	      break;

	    default:
	      sc.contents = CONTENTS_CODE;
	    }
	}
      else
	{
	  sc.contents = CONTENTS_CODE;
	}

      sysroff_swap_sc_out (file, &sc);
      scount++;
    }
  return scount;
}