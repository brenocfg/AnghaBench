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
struct ui_file {int dummy; } ;
struct reggroup {int dummy; } ;
struct regcache {TYPE_1__* descr; } ;
struct gdbarch {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  enum regcache_dump_what { ____Placeholder_regcache_dump_what } regcache_dump_what ;
struct TYPE_2__ {int legacy_p; int nr_raw_registers; int nr_cooked_registers; int sizeof_raw_registers; int sizeof_raw_register_valid_p; int* register_offset; int* sizeof_register; struct gdbarch* gdbarch; } ;

/* Variables and functions */
 long DEPRECATED_REGISTER_BYTE (int) ; 
 int DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 int DEPRECATED_REGISTER_VIRTUAL_SIZE (int) ; 
 int MAX_REGISTER_SIZE ; 
 int NUM_PSEUDO_REGS ; 
 int NUM_REGS ; 
 char* REGISTER_NAME (int) ; 
 int /*<<< orphan*/  TARGET_BYTE_ORDER ; 
 int TYPE_LENGTH (int /*<<< orphan*/ ) ; 
 char* TYPE_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  dump_endian_bytes (struct ui_file*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  fprintf_unfiltered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 scalar_t__ gdbarch_register_reggroup_p (struct gdbarch*,int,struct reggroup*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  null_cleanup ; 
 int /*<<< orphan*/  regcache_cooked_read (struct regcache*,int,unsigned char*) ; 
 int regcache_dump_cooked ; 
 int regcache_dump_groups ; 
 int regcache_dump_raw ; 
 int /*<<< orphan*/  regcache_raw_read (struct regcache*,int,unsigned char*) ; 
 int /*<<< orphan*/  regcache_valid_p (struct regcache*,int) ; 
 int /*<<< orphan*/  reggroup_name (struct reggroup*) ; 
 struct reggroup* reggroup_next (struct gdbarch*,struct reggroup*) ; 
 int /*<<< orphan*/  register_type (struct gdbarch*,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,int) ; 
 int /*<<< orphan*/  xfree ; 

__attribute__((used)) static void
regcache_dump (struct regcache *regcache, struct ui_file *file,
	       enum regcache_dump_what what_to_dump)
{
  struct cleanup *cleanups = make_cleanup (null_cleanup, NULL);
  struct gdbarch *gdbarch = regcache->descr->gdbarch;
  int regnum;
  int footnote_nr = 0;
  int footnote_register_size = 0;
  int footnote_register_offset = 0;
  int footnote_register_type_name_null = 0;
  long register_offset = 0;
  unsigned char buf[MAX_REGISTER_SIZE];

#if 0
  fprintf_unfiltered (file, "legacy_p %d\n", regcache->descr->legacy_p);
  fprintf_unfiltered (file, "nr_raw_registers %d\n",
		      regcache->descr->nr_raw_registers);
  fprintf_unfiltered (file, "nr_cooked_registers %d\n",
		      regcache->descr->nr_cooked_registers);
  fprintf_unfiltered (file, "sizeof_raw_registers %ld\n",
		      regcache->descr->sizeof_raw_registers);
  fprintf_unfiltered (file, "sizeof_raw_register_valid_p %ld\n",
		      regcache->descr->sizeof_raw_register_valid_p);
  fprintf_unfiltered (file, "NUM_REGS %d\n", NUM_REGS);
  fprintf_unfiltered (file, "NUM_PSEUDO_REGS %d\n", NUM_PSEUDO_REGS);
#endif

  gdb_assert (regcache->descr->nr_cooked_registers
	      == (NUM_REGS + NUM_PSEUDO_REGS));

  for (regnum = -1; regnum < regcache->descr->nr_cooked_registers; regnum++)
    {
      /* Name.  */
      if (regnum < 0)
	fprintf_unfiltered (file, " %-10s", "Name");
      else
	{
	  const char *p = REGISTER_NAME (regnum);
	  if (p == NULL)
	    p = "";
	  else if (p[0] == '\0')
	    p = "''";
	  fprintf_unfiltered (file, " %-10s", p);
	}

      /* Number.  */
      if (regnum < 0)
	fprintf_unfiltered (file, " %4s", "Nr");
      else
	fprintf_unfiltered (file, " %4d", regnum);

      /* Relative number.  */
      if (regnum < 0)
	fprintf_unfiltered (file, " %4s", "Rel");
      else if (regnum < NUM_REGS)
	fprintf_unfiltered (file, " %4d", regnum);
      else
	fprintf_unfiltered (file, " %4d", (regnum - NUM_REGS));

      /* Offset.  */
      if (regnum < 0)
	fprintf_unfiltered (file, " %6s  ", "Offset");
      else
	{
	  fprintf_unfiltered (file, " %6ld",
			      regcache->descr->register_offset[regnum]);
	  if (register_offset != regcache->descr->register_offset[regnum]
	      || register_offset != DEPRECATED_REGISTER_BYTE (regnum)
	      || (regnum > 0
		  && (regcache->descr->register_offset[regnum]
		      != (regcache->descr->register_offset[regnum - 1]
			  + regcache->descr->sizeof_register[regnum - 1])))
	      )
	    {
	      if (!footnote_register_offset)
		footnote_register_offset = ++footnote_nr;
	      fprintf_unfiltered (file, "*%d", footnote_register_offset);
	    }
	  else
	    fprintf_unfiltered (file, "  ");
	  register_offset = (regcache->descr->register_offset[regnum]
			     + regcache->descr->sizeof_register[regnum]);
	}

      /* Size.  */
      if (regnum < 0)
	fprintf_unfiltered (file, " %5s ", "Size");
      else
	{
	  fprintf_unfiltered (file, " %5ld",
			      regcache->descr->sizeof_register[regnum]);
	  if ((regcache->descr->sizeof_register[regnum]
	       != DEPRECATED_REGISTER_RAW_SIZE (regnum))
	      || (regcache->descr->sizeof_register[regnum]
		  != DEPRECATED_REGISTER_VIRTUAL_SIZE (regnum))
	      || (regcache->descr->sizeof_register[regnum]
		  != TYPE_LENGTH (register_type (regcache->descr->gdbarch,
						 regnum)))
	      )
	    {
	      if (!footnote_register_size)
		footnote_register_size = ++footnote_nr;
	      fprintf_unfiltered (file, "*%d", footnote_register_size);
	    }
	  else
	    fprintf_unfiltered (file, " ");
	}

      /* Type.  */
      {
	const char *t;
	if (regnum < 0)
	  t = "Type";
	else
	  {
	    static const char blt[] = "builtin_type";
	    t = TYPE_NAME (register_type (regcache->descr->gdbarch, regnum));
	    if (t == NULL)
	      {
		char *n;
		if (!footnote_register_type_name_null)
		  footnote_register_type_name_null = ++footnote_nr;
		xasprintf (&n, "*%d", footnote_register_type_name_null);
		make_cleanup (xfree, n);
		t = n;
	      }
	    /* Chop a leading builtin_type.  */
	    if (strncmp (t, blt, strlen (blt)) == 0)
	      t += strlen (blt);
	  }
	fprintf_unfiltered (file, " %-15s", t);
      }

      /* Leading space always present.  */
      fprintf_unfiltered (file, " ");

      /* Value, raw.  */
      if (what_to_dump == regcache_dump_raw)
	{
	  if (regnum < 0)
	    fprintf_unfiltered (file, "Raw value");
	  else if (regnum >= regcache->descr->nr_raw_registers)
	    fprintf_unfiltered (file, "<cooked>");
	  else if (!regcache_valid_p (regcache, regnum))
	    fprintf_unfiltered (file, "<invalid>");
	  else
	    {
	      regcache_raw_read (regcache, regnum, buf);
	      fprintf_unfiltered (file, "0x");
	      dump_endian_bytes (file, TARGET_BYTE_ORDER, buf,
				 DEPRECATED_REGISTER_RAW_SIZE (regnum));
	    }
	}

      /* Value, cooked.  */
      if (what_to_dump == regcache_dump_cooked)
	{
	  if (regnum < 0)
	    fprintf_unfiltered (file, "Cooked value");
	  else
	    {
	      regcache_cooked_read (regcache, regnum, buf);
	      fprintf_unfiltered (file, "0x");
	      dump_endian_bytes (file, TARGET_BYTE_ORDER, buf,
				 DEPRECATED_REGISTER_VIRTUAL_SIZE (regnum));
	    }
	}

      /* Group members.  */
      if (what_to_dump == regcache_dump_groups)
	{
	  if (regnum < 0)
	    fprintf_unfiltered (file, "Groups");
	  else
	    {
	      const char *sep = "";
	      struct reggroup *group;
	      for (group = reggroup_next (gdbarch, NULL);
		   group != NULL;
		   group = reggroup_next (gdbarch, group))
		{
		  if (gdbarch_register_reggroup_p (gdbarch, regnum, group))
		    {
		      fprintf_unfiltered (file, "%s%s", sep, reggroup_name (group));
		      sep = ",";
		    }
		}
	    }
	}

      fprintf_unfiltered (file, "\n");
    }

  if (footnote_register_size)
    fprintf_unfiltered (file, "*%d: Inconsistent register sizes.\n",
			footnote_register_size);
  if (footnote_register_offset)
    fprintf_unfiltered (file, "*%d: Inconsistent register offsets.\n",
			footnote_register_offset);
  if (footnote_register_type_name_null)
    fprintf_unfiltered (file, 
			"*%d: Register type's name NULL.\n",
			footnote_register_type_name_null);
  do_cleanups (cleanups);
}