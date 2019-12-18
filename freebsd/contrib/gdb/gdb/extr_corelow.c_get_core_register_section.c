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
struct regset {int /*<<< orphan*/  (* supply_regset ) (struct regset const*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ;} ;
struct bfd_section {int dummy; } ;
typedef  int /*<<< orphan*/  file_ptr ;
typedef  int /*<<< orphan*/  bfd_size_type ;
struct TYPE_3__ {int /*<<< orphan*/  (* core_read_registers ) (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ PIDGET (int /*<<< orphan*/ ) ; 
 char* alloca (int /*<<< orphan*/ ) ; 
 struct bfd_section* bfd_get_section_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bfd_get_section_contents (int /*<<< orphan*/ ,struct bfd_section*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_section_size (int /*<<< orphan*/ ,struct bfd_section*) ; 
 scalar_t__ bfd_section_vma (int /*<<< orphan*/ ,struct bfd_section*) ; 
 int /*<<< orphan*/  core_bfd ; 
 scalar_t__ core_gdbarch ; 
 TYPE_1__* core_vec ; 
 int /*<<< orphan*/  current_regcache ; 
 int /*<<< orphan*/  gdb_assert (TYPE_1__*) ; 
 struct regset* gdbarch_regset_from_core_section (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ gdbarch_regset_from_core_section_p (scalar_t__) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  stub1 (struct regset const*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,char*,...) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xstrdup (char*) ; 
 char* xstrprintf (char*,char*,scalar_t__) ; 

__attribute__((used)) static void
get_core_register_section (char *name,
			   int which,
			   char *human_name,
			   int required)
{
  static char *section_name = NULL;
  struct bfd_section *section;
  bfd_size_type size;
  char *contents;

  xfree (section_name);
  if (PIDGET (inferior_ptid))
    section_name = xstrprintf ("%s/%d", name, PIDGET (inferior_ptid));
  else
    section_name = xstrdup (name);

  section = bfd_get_section_by_name (core_bfd, section_name);
  if (! section)
    {
      if (required)
	warning ("Couldn't find %s registers in core file.\n", human_name);
      return;
    }

  size = bfd_section_size (core_bfd, section);
  contents = alloca (size);
  if (! bfd_get_section_contents (core_bfd, section, contents,
				  (file_ptr) 0, size))
    {
      warning ("Couldn't read %s registers from `%s' section in core file.\n",
	       human_name, name);
      return;
    }

  if (core_gdbarch && gdbarch_regset_from_core_section_p (core_gdbarch))
    {
      const struct regset *regset;

      regset = gdbarch_regset_from_core_section (core_gdbarch, name, size);
      if (regset == NULL)
	{
	  if (required)
	    warning ("Couldn't recognize %s registers in core file.\n",
		     human_name);
	  return;
	}

      regset->supply_regset (regset, current_regcache, -1, contents, size);
      return;
    }

  gdb_assert (core_vec);
  core_vec->core_read_registers (contents, size, which,
				 ((CORE_ADDR)
				  bfd_section_vma (core_bfd, section)));
}