#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct type {int dummy; } ;
struct symtab {int /*<<< orphan*/  language; } ;
struct TYPE_2__ {scalar_t__ entry_point; scalar_t__ deprecated_entry_file_lowpc; scalar_t__ deprecated_entry_file_highpc; } ;
struct objfile {TYPE_1__ ei; } ;
struct dieinfo {scalar_t__ at_low_pc; scalar_t__ at_high_pc; int die_length; int /*<<< orphan*/  at_comp_dir; int /*<<< orphan*/  at_name; int /*<<< orphan*/ * at_producer; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 int FT_NUM_MEMBERS ; 
 int /*<<< orphan*/  cu_language ; 
 int /*<<< orphan*/  decode_line_numbers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct symtab* end_symtab (scalar_t__,struct objfile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_utypes ; 
 struct type** ftypes ; 
 int /*<<< orphan*/  handle_producer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lnbase ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct type**,int /*<<< orphan*/ ,int) ; 
 int numutypes ; 
 int /*<<< orphan*/  process_dies (char*,char*,struct objfile*) ; 
 int /*<<< orphan*/  record_debugformat (char*) ; 
 int /*<<< orphan*/  set_cu_language (struct dieinfo*) ; 
 int /*<<< orphan*/  start_symtab (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct type** utypes ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
read_file_scope (struct dieinfo *dip, char *thisdie, char *enddie,
		 struct objfile *objfile)
{
  struct cleanup *back_to;
  struct symtab *symtab;

  if (objfile->ei.entry_point >= dip->at_low_pc &&
      objfile->ei.entry_point < dip->at_high_pc)
    {
      objfile->ei.deprecated_entry_file_lowpc = dip->at_low_pc;
      objfile->ei.deprecated_entry_file_highpc = dip->at_high_pc;
    }
  set_cu_language (dip);
  if (dip->at_producer != NULL)
    {
      handle_producer (dip->at_producer);
    }
  numutypes = (enddie - thisdie) / 4;
  utypes = (struct type **) xmalloc (numutypes * sizeof (struct type *));
  back_to = make_cleanup (free_utypes, NULL);
  memset (utypes, 0, numutypes * sizeof (struct type *));
  memset (ftypes, 0, FT_NUM_MEMBERS * sizeof (struct type *));
  start_symtab (dip->at_name, dip->at_comp_dir, dip->at_low_pc);
  record_debugformat ("DWARF 1");
  decode_line_numbers (lnbase);
  process_dies (thisdie + dip->die_length, enddie, objfile);

  symtab = end_symtab (dip->at_high_pc, objfile, 0);
  if (symtab != NULL)
    {
      symtab->language = cu_language;
    }
  do_cleanups (back_to);
}